/**
  ******************************************************************************
  * File Name          : DOUT_Methods.c
  * Description        : Methods for DOUT Class
  ******************************************************************************
  *				TO DO
  *		OBSLUGA CZASU DLUGOSCI ZMIANY
  *		//SetOverload(int Overload);
  ******************************************************************************
  */

#include "DOUT.h"
#include "../../Logger/logger.h"

/* Function declarations -----------------------------------------------*/
METHOD_ERROR DOUT_Init(struct DOUT *Object, GPIO_TypeDef *GPIO_Port, uint16_t GPIO_Pin){
	Object->GPIO_Pin=GPIO_Pin;
	Object->GPIO_Port=GPIO_Port;
	DOUT_SetValue(Object, 0);
	return ERROR_OK;
}

METHOD_ERROR DOUT_SetValue(struct DOUT *Object, bool Value){
	if (Object->Value == Value) return ERROR_CBC;
	int ERROR_VALUE;
	if (Object->Value) ERROR_VALUE = DOUT_SwitchOff(Object, 0);
	if (!Object->Value)ERROR_VALUE = DOUT_SwitchOn(Object, 0);
	return ERROR_VALUE;
}

METHOD_ERROR DOUT_Switch(struct DOUT *Object, int Time){
	METHOD_ERROR ERROR_VALUE = 1;

	if (Object->Value){
		ERROR_VALUE = DOUT_SwitchOff(Object, Time);
	}else if(!Object->Value){
		ERROR_VALUE = DOUT_SwitchOn(Object, Time);
	}

	return ERROR_VALUE;
}

METHOD_ERROR DOUT_SwitchOn(struct DOUT *Object, int Time){
	if (Object->Value) return ERROR_CBC;
	HAL_GPIO_WritePin(Object->GPIO_Port, Object->GPIO_Pin, 1);
	Object->Value = 1;
	OnValueChange(Object->ID);
	OnSwitchOn(Object->ID);
#if (_TCP_DEBUG == 1)
	AddToLog("Turned ON", LOG_ACT);
#endif
	return ERROR_OK;
}

METHOD_ERROR DOUT_SwitchOff(struct DOUT *Object, int Time){
	if (!Object->Value) return ERROR_CBC;
	HAL_GPIO_WritePin(Object->GPIO_Port, Object->GPIO_Pin, 0);
	Object->Value = 0;
	OnValueChange(Object->ID);
	OnSwitchOff(Object->ID);
#if (_TCP_DEBUG == 1)
	AddToLog("Turned ON", LOG_ACT);
#endif
	return ERROR_OK;
}

