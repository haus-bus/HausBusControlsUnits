/*
 * Counter.cpp
 *
 *  Created on: 22.10.2015
 *      Author: Viktor Pankraz
 */

#include "Counter.h"

#include <ErrorMessage.h>

const uint8_t Counter::debugLevel( DEBUG_LEVEL_OFF );

Counter::Response::Parameter& Counter::Response::setConfiguration()
{
   controlFrame.setDataLength( sizeof( getResponse() ) + sizeof( getParameter().configuration ) );
   setResponse( CONFIGURATION );
   return getParameter();
}

Counter::Counter( uint8_t _id )
{
   Object::setId( ( ClassId::COUNTER << 8 ) | _id );
}

bool Counter::handleRequest( HBCP* message )
{
   HBCP::ControlFrame& cf = message->controlFrame;
   Command* data = reinterpret_cast<Command*>( cf.getData() );

   if ( cf.isCommand( Command::GET_CONFIGURATION ) )
   {
      DEBUG_H1( FSTR( ".getConfiguration()" ) );
      Response response( getId(), *message );
      configuration->get( response.setConfiguration().configuration );
      response.queue( getObject( message->header.getSenderId() ) );
   }
   else if ( cf.isCommand( Command::GET_VALUE ) )
   {
      DEBUG_H1( FSTR( ".getValue()" ) );
      Response response( getId(), *message );
      response.setValue( value );
      response.queue( getObject( message->header.getSenderId() ) );
   }
   else if ( cf.isCommand( Command::SET_CONFIGURATION ) )
   {
      DEBUG_H1( FSTR( ".setConfiguration()" ) );
      configuration->set( data->parameter.setConfiguration );
      mode = configuration->getMode();
      timeToReport = configuration->reportTime;
   }
   else if ( cf.isCommand( Command::SET_VALUE ) )
   {
      DEBUG_H3( FSTR( ".setValue(" ), value, ')' );
      value = data->parameter.value;
   }
   else
   {
      return false;
   }

   return true;
}

bool Counter::notifyEvent( const Event& event )
{
   if ( event.isEvWakeup() )
   {
      if ( inStartUp() )
      {
         setConfiguration( ConfigurationManager::getConfiguration<EepromConfiguration>( id ) );
         if ( configuration )
         {
            mode = configuration->getMode();
            timeToReport = configuration->reportTime;
            value = configuration->value;
            lastValue = value;
            SET_STATE_L1( RUNNING );
         }
         else
         {
            terminate();
            ErrorMessage::notifyOutOfMemory( id );
            return true;
         }
      }
      tick();
   }
   else if ( event.isEvMessage() )
   {
      return handleRequest( event.isEvMessage()->getMessage() );
   }

   return false;
}

void Counter::updateState( uint8_t newState )
{

   if ( ( mode.falling && !newState ) || ( mode.rising && newState ) )
   {
      if ( mode.increment )
      {
         value++;
      }
      else
      {
         value--;
      }
   }
}

void Counter::tick()
{
   setSleepTime( SystemTime::MIN );

   // save the current value in eeprom to restore after reset
   configuration->value.update( value );

   if ( timeToReport )
   {
      if ( --timeToReport == 0 )
      {
         timeToReport = configuration->reportTime;
         Response event( getId() );
         event.setStatus( value - lastValue );
         event.queue();
         lastValue = value;
      }
   }
}
