/*
 * AR8SystemHw.h
 *
 *  Created on: 06.08.2014
 *      Author: Viktor Pankraz
 */

#ifndef Electronics_SystemBoards_AR8_AR8_Boards_AR8SystemHw_H
#define Electronics_SystemBoards_AR8_AR8_Boards_AR8SystemHw_H

#include "AR8_Board.h"
#include <HbcDeviceHw.h>
#include <InternalEeprom.h>

class AR8SystemHw : public HbcDeviceHw
{
   public:

      static const uint16_t TCC1_PRESCALER = 1024;

      ////    Constructors and destructors    ////

      AR8SystemHw();

      ////    Operations    ////

   private:

      void configure();

      void configureDaliLine();

      void configureEthernet();

      void configureRs485();

      void configureTwi();

      void configureLogicalButtons();

      void configureSlots();

      void configureZeroCrossDetection();

      ////    Additional operations    ////

   public:

      InternalEeprom* getInternalEeprom() const;

      ////    Attributes    ////

      ////    Relations and components    ////

   protected:

      bool hasDimmerInSlotsOneToFour;

};

#endif