/*
 * AR8System.h
 *
 *  Created on: 06.08.2014
 *      Author: Viktor Pankraz
 */

#ifndef Systems_HomeAutomationSystems_AR8System_H
#define Systems_HomeAutomationSystems_AR8System_H

#include "AR8SystemHw.h"

#include <HwUnits/DigitalPort.h>
#include <HbcDevice.h>


class AR8System : public HbcDevice
{
   ////    Constructors and destructors    ////

   public:

      AR8System();

      ////    Operations    ////

      ////    Additional operations    ////

      ////    Relations and components    ////

   protected:

      DigitalPort digitalPortE;

      DigitalPort digitalPortF;

      AR8SystemHw hardware;
};

#endif
