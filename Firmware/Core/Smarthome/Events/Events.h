/**
  ******************************************************************************
  * File Name          : Events.h
  * Description        : All events in system
  ******************************************************************************
  *
  *
  ******************************************************************************
  */

#ifndef _EVENTS_H
#define _EVENTS_H

#include "../Smarthome/Classes/CLU/CLU.h"

//#include "../Smarthome/Classes/DIN/Buttons.h"
#include "../Smarthome/Classes/DIMM/DIMM.h"
#include "../Smarthome/Classes/DOUT/DOUT.h"
#include "../Smarthome/Classes/DIN/DIN.h"
#include "../Smarthome/Classes/LED/LED.h"


/* Function prototypes -----------------------------------------------*/

// DOUT + DIN + LED
METHOD_ERROR OnValueChange(int ID);
METHOD_ERROR OnSwitchOn(int ID);
METHOD_ERROR OnSwitchOff(int ID);

// DIN

METHOD_ERROR OnShortPress(int ID);
METHOD_ERROR OnLongPress(int ID);
METHOD_ERROR OnHold(int ID);
METHOD_ERROR OnClick(int ID);

// RGBW

//OnValueRise();
//OnValueLower();
//OnOutOfRange();


#endif
