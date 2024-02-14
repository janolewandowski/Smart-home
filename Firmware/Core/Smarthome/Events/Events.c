/**
  ******************************************************************************
  * File Name          : Events.c
  * Description        : All events in system
  ******************************************************************************
  *
  *
  ******************************************************************************
  */

#include "../../Smarthome/Events/Events.h"


//extern struct DOUT LED_OK;

/* Function declarations -----------------------------------------------*/
// DOUT + DIN + LED
METHOD_ERROR OnValueChange(int ID){
	//variable = ID;
	return ERROR_OK;
}

METHOD_ERROR OnSwitchOn(int ID){
	//if (ID == 0x07) DOUT_Switch(&LED_OK,0);
	return ERROR_OK;
}

METHOD_ERROR OnSwitchOff(int ID){
	return ERROR_OK;
}

// DIN

METHOD_ERROR OnShortPress(int ID){
	return ERROR_OK;
}

METHOD_ERROR OnLongPress(int ID){
	return ERROR_OK;
}

METHOD_ERROR OnHold(int ID){
	return ERROR_OK;
}

METHOD_ERROR OnClick(int ID){
	int ERROR_VALUE;
	switch(ID){
	case 0x00:
		//ERROR_VALUE = Switch(&Swiatlo_Kuchnia_Obwod_1);
		//ERROR_VALUE = Switch(&Swiatlo_Kuchnia_Obwod_2);
		break;
	case 0x01:
		//ERROR_VALUE = Switch();
		break;
	case 0x02:
		//ERROR_VALUE = Switch();
		break;
	case 0x03:
		//ERROR_VALUE = Switch();
		break;
	case 0x04:
		//ERROR_VALUE = Switch();
		break;
	case 0x05:
		//ERROR_VALUE = Switch();
		break;
	default:
		ERROR_VALUE = ERROR_NOID;
	}

	return ERROR_VALUE;
}

// RGBW

//OnValueRise();
//OnValueLower();
//OnOutOfRange();
