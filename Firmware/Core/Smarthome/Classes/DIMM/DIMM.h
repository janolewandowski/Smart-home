/**
  ******************************************************************************
  * File Name          : DIN_Methods.h
  * Description        : Methods for DIN Class
  ******************************************************************************
  *
  *
  ******************************************************************************
  */
#ifndef _DIMM_H
#define _DIMM_H
#include "stdbool.h"
#include "DIMM.h"

#include "../Smarthome/Classes/CLU/CLU.h"
#include "../../../Smarthome/Events/Events.h"
#include "../../../PCA9685/PCA9685.h"

struct DIMM {
  int ID;									// Adres obiektu
  int Value;								// Wartość jasności
  int RampTime;								// Wartość opóznienia przy zmianie intesywaności świecenia w ms
  int MinValue, MaxValue;					// Wartości max i min jakie może przyjąc Value
  int StartLevel;							// Aktualna wartość progu załączenia wyjścia
  int DimmingEdge;							// Aktualny typ rodzaju ściemniania
  int HoldValue;							// ?

  int PCA_Channel;							// Adres kanału modułu PWM


};

/* Function prototypes -----------------------------------------------*/
METHOD_ERROR DIMM_SwitchOn(struct DIMM *Object, int Time, int Ramp);
METHOD_ERROR DIMM_SwitchOff(struct DIMM *Object, int Time, int Ramp);
METHOD_ERROR DIMM_Switch(struct DIMM *Object, int Time, int Ramp);

METHOD_ERROR DIMM_SetValue(struct DIMM *Object, int Value, int Ramp);
METHOD_ERROR DIMM_SetRampTime(struct DIMM *Object, int RampTime);
METHOD_ERROR DIMM_SetMaxValue(struct DIMM *Object, int Value);
METHOD_ERROR DIMM_SetMinValue(struct DIMM *Object, int Value);
METHOD_ERROR DIMM_DimmingEdge(struct DIMM *Object, bool Value); 		//trailingEdge or leading edge
METHOD_ERROR DIMM_HoldValue(struct DIMM *Object, int Ramp);
#endif
