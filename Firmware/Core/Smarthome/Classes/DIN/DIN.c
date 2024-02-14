/**
  ******************************************************************************
  * File Name          : DIN.c
  * Description        : DIN Class
  ******************************************************************************
  *
  *
  ******************************************************************************
  */
/*
     ____________________________
____|                            |_____________
     <----long-press min-->
                           ^
                           |_Long press detected
     ______     _____
____|      |___|     |_________________________
                     ^
                     |_Double press detected
     ______
____|      |___________________________________
           <------->
              ^    ^
              |    |_Single press detected
              |_ Double press gap max.
*/
#include "DIN.h"

/* Function declarations -----------------------------------------------*/

METHOD_ERROR SetInertion(struct DIN *Object, int Inertion){
	Object->Inertion = Inertion;
	return ERROR_OK;
}

METHOD_ERROR SetHoldDelay(struct DIN *Object, int HoldDelay){
	Object->HoldDelay = HoldDelay;
	return ERROR_OK;
}

METHOD_ERROR SetHoldInterval(struct DIN *Object, int HoldInterval){
	Object->HoldInterval = HoldInterval;
	return ERROR_OK;
}

DIN_Event DIN_Process(struct DIN *Object){

  DIN_Event retval = NO_PRESS;

  if (HAL_GetTick() < Object->lastTime) Object->lastTime = HAL_GetTick();																// wrapped around
  if ((Object->lastTime + Object->Inertion) > HAL_GetTick())  return NO_PRESS;															// not enough time has passed to debounce, try again

  Object->lastTime = HAL_GetTick();																								// have waited DEBOUNCE milliseconds, reset the timer
  Object->state = HAL_GPIO_ReadPin(Object->GPIO_Port, Object->GPIO_Pin);  																// read the button

	if (Object->state != Object->lastState) {																							// BUTTON PRESSED AFTER DEBOUNCE
		  if (Object->state == 0) {																								// just pressed
			  Object->button_pressed_ts = HAL_GetTick();
			  Object->long_press_pending = true;
		  }else if (Object->state == 1) {          																				// just released
			  Object-> button_released_ts = HAL_GetTick();
				 if(Object->double_pending)
				 {
					 retval = DOUBLE_PRESS;
					 Object->double_pending = false;
				 }
				 else if (Object->button_released_ts - Object->button_pressed_ts < DOUBLE_GAP_MILLIS_MAX)
				 {
					 Object->double_pending = true;
				 }
		  }
	}

	if (Object->state && Object->double_pending && HAL_GetTick() - Object->button_released_ts >= DOUBLE_GAP_MILLIS_MAX && Object->button_released_ts - Object->button_pressed_ts < LONG_MILLIS_MIN){
		retval = SINGLE_PRESS;
		Object->long_press_pending = false;
		Object->double_pending = false;
	}else if(Object->long_press_pending && !Object->state && HAL_GetTick() - Object->button_pressed_ts > LONG_MILLIS_MIN){
		retval = LONG_PRESS;
		Object->double_pending = false;
		//long_press_pending = false; //long press only once if uncommented
	}

	Object->lastState = Object->state;
    return retval;
}
//
//DIN_Event DIN_Process(struct DIN *Object){
//
//  DIN_Event retval;
//
//  if (HAL_GetTick() < Object->lastTime) {
//     Object->lastTime = HAL_GetTick();																// wrapped around
//  }
//
//  if ((Object->lastTime + Object->Inertion) > HAL_GetTick())  return NO_PRESS;						// not enough time has passed to debounce, try again
//
//  Object->lastTime = HAL_GetTick();																	// have waited DEBOUNCE milliseconds, reset the timer
//
//  Object->state = HAL_GPIO_ReadPin(Object->GPIO_Port, Object->GPIO_Pin);  							// read the button
//
//			if (Object->state == Object->lastState) {												// BUTTON PRESSED AFTER DEBOUNCE
//
//				  if ((Object->lastState == 0) && (Object->state == 0)) {								// just pressed
//					  Object->button_pressed_ts = HAL_GetTick();
//					  while (!HAL_GPIO_ReadPin(Object->GPIO_Port, Object->GPIO_Pin));
//					  return SINGLE_PRESS;
//				  }else if ((Object->lastState == 1) && (Object->state == 1)) {          				// just released
//					  Object->button_released_ts = HAL_GetTick();
//
//						  if(Object->double_pending){													// If double decision pending...
//							  retval = DOUBLE_PRESS;
//							  Object->double_pending = false;
//						  }
//						  else{
//							  Object->double_pending = true;
//						  }
//
//					  }
//			  Object->Value = !Object->state;  															// remember, digital HIGH means NOT pressed
//			}
//
//			// If button-up and double-press gap time expired, it was a single press
//			if( Object->state && Object->double_pending && ((HAL_GetTick() - Object->button_released_ts) > DOUBLE_GAP_MILLIS_MAX ))
//			{
//				Object->double_pending = false;
//				retval = SINGLE_PRESS;
//			}
//			// else if button-down for long-press...
//			else if(!Object->state && ((HAL_GetTick() - Object->button_pressed_ts) > LONG_MILLIS_MIN )){
//				retval = LONG_PRESS;
//				Object->double_pending = false;
//			}
//
//    Object->lastState = Object->state;   // keep a running tally of the buttons
//    return retval;
//}
