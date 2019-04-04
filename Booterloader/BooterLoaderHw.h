/*
 * BooterLoaderHw.h
 *
 *  Created on: 28.08.2014
 *      Author: Viktor Pankraz
 */

#ifndef BooterLoaderHw_H
#define BooterLoaderHw_H

#include <HbcDeviceHw.h>

class Checksum;
class ModuleId;

class BooterLoaderHw : public HbcDeviceHw
{
   ////    Constructors and destructors    ////

   public:

      inline BooterLoaderHw()
      {
         // configure ports
         PORTR.DIRSET = Pin0 | Pin1;

         // set statusLed to green
         PORTR.OUTSET = Pin1;
      }

      ////    Operations    ////

      void copyBooter();
};

#endif
