/**
  ******************************************************************************
  * File Name          : DIN.h
  * Description        : DIN Class
  ******************************************************************************
  *
  *
  ******************************************************************************
  */
#ifndef _DIN_H
#define _DIN_H

#include "stdbool.h"

#include "../Smarthome/Classes/CLU/CLU.h"
#include "DIN.h"
#include "../../../Smarthome/Events/Events.h"

#define DOUBLE_GAP_MILLIS_MAX 350 //250
#define LONG_MILLIS_MIN 800

//extern uint32_t ticks;

typedef enum
{
    NO_PRESS,
    SINGLE_PRESS,
    LONG_PRESS,
    DOUBLE_PRESS
} DIN_Event ;

/* Class DIN -----------------------------------------------*/
struct DIN{
	int ID;									// Adres obiektu
	bool Value;								// Stan wejścia

	int Inertion;							// Opóznienie wejścia - debouncing
	int HoldDelay;							// Czas po jakim po wcisnięciu i przytrzymaniu wywoływana jest funckcja OnHold();
	int HoldInterval;						// Odstęp cykliczny po jakim oidczas trzymania przycisku wywoływane są kolejne zdarzenia OnHold();

	GPIO_TypeDef *GPIO_Port;
	uint16_t GPIO_Pin;

	bool state;
	bool lastState;
	uint32_t lastTime;

	uint32_t button_pressed_ts;
	uint32_t button_released_ts;
	bool long_press_pending;
	bool double_pending;

	METHOD_ERROR (*SetInertion)();
};


/* Function prototypes -----------------------------------------------*/
METHOD_ERROR SetInertion(struct DIN *Object, int Inertion);
METHOD_ERROR DIN_SetHoldDelay(struct DIN *Object,int HoldDelay);
METHOD_ERROR DIN_SetHoldInterval(struct DIN *Object, int HoldInterval);

DIN_Event DIN_Process(struct DIN *Object);

#endif
