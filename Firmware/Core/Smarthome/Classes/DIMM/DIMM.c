/**
  ******************************************************************************
  * File Name          : DIMM.c
  * Description        : DIMM Class
  ******************************************************************************
  *
  *
  ******************************************************************************
  */
#include "stdbool.h"
#include "DIMM.h"

/* Function declarations -----------------------------------------------*/

METHOD_ERROR DIMM_SwitchOn(struct DIMM *Object, int Time, int Ramp){
	if (Object->Value) return ERROR_CBC;

	if (PCA9685_SetPwm(Object->PCA_Channel, 0, 4095)) return ERROR_PCA;

	Object->Value = 1;
	OnValueChange(Object->ID);
	OnSwitchOn(Object->ID);
	return ERROR_OK;
}
METHOD_ERROR DIMM_SwitchOff(struct DIMM *Object, int Time, int Ramp){
	if (!Object->Value) return ERROR_CBC;

	if (PCA9685_SetPwm(Object->PCA_Channel, 4095, 0)) return ERROR_PCA;

	Object->Value = 0;
	OnValueChange(Object->ID);
	OnSwitchOff(Object->ID);
	return ERROR_OK;
}
METHOD_ERROR DIMM_Switch(struct DIMM *Object, int Time, int Ramp){
	METHOD_ERROR ERROR_VALUE;
	if (Object->Value){
		ERROR_VALUE = DIMM_SwitchOff(Object, Time, Ramp);
	}else {
		ERROR_VALUE = DIMM_SwitchOn(Object, Time, Ramp);
	}
	return ERROR_VALUE;
}
METHOD_ERROR DIMM_SetValue(struct DIMM *Object, int Value, int Ramp){
	if (Value > Object->MaxValue) Value = Object->MaxValue;
	if (Value < Object->MinValue) Value = Object->MinValue;
	return ERROR_OK;
}
METHOD_ERROR DIMM_SetRampTime(struct DIMM *Object, int RampTime){
	Object->RampTime = RampTime;
	return ERROR_OK;
}

METHOD_ERROR DIMM_SetMaxValue(struct DIMM *Object, int Value){
	Object->MaxValue = Value;
	return ERROR_OK;
}

METHOD_ERROR DIMM_SetMinValue(struct DIMM *Object, int Value){
	Object->MinValue = Value;
	return ERROR_OK;
}
METHOD_ERROR DIMM_DimmingEdge(struct DIMM *Object, bool Value){
	Object->DimmingEdge = Value;
	return ERROR_OK;
}

METHOD_ERROR DIMM_HoldValue(struct DIMM *Object, int Ramp){
	//Object->HoldValue = Value;
	return ERROR_OK;
}

