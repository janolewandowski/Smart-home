/**
  ******************************************************************************
  * File Name          : DOUT_Methods.h
  * Description        : Methods for DOUT Class
  ******************************************************************************
  *				TO DO
  *		OBSLUGA CZASU DLUGOSCI ZMIANY
  *		//SetOverload(int Overload);
  ******************************************************************************
  */

#ifndef _DOUT_H
#define _DOUT_H

#include "stdbool.h"
#include "../Smarthome/Classes/CLU/CLU.h"
#include "../../../inc/gpio.h"
#include "../../../Smarthome/Events/Events.h"

struct DOUT{
  int ID;									// Adres obiektu
  bool Value;								// Stan wyjścia

  GPIO_TypeDef *GPIO_Port;
  uint16_t GPIO_Pin;

  bool state;
  bool lastState;
  uint32_t lastTime;
};

/* Function prototypes -----------------------------------------------*/
METHOD_ERROR DOUT_SetValue(struct DOUT *Object, bool Value);
METHOD_ERROR DOUT_Switch(struct DOUT *Object, int Time);
METHOD_ERROR DOUT_SwitchOn(struct DOUT *Object, int Time);
METHOD_ERROR DOUT_SwitchOff(struct DOUT *Object, int Time);

#endif
