/**
  ******************************************************************************
  * File Name          : LED_Methods.h
  * Description        : Methods for LED Class
  ******************************************************************************
  *
  *
  ******************************************************************************
  */
#ifndef _LED_H
#define _LED_H

#include "LED.h"
#include "../Smarthome/Classes/CLU/CLU.h"

struct LED {
  int ID;									// Adres obiektu
  int Value;								// Wartość jasności wg modelu HSV 0 - 100
  int Hue;									// Wartość koloru barwy wg modelu HSV 0 - 360
  int Saturation;							// Wartość nasycenia barwy wg modelu HSV 0 - 100
  int RedValue, GreenValue, 				// Wartości składowych kolorów 0 - 255
  	  BlueValue, WhiteValue;
  //hex										// Wartość kolory wg modelu RGB #RRGGBB - HEX
  int RampTime;								// Wartość czasu narastania wartości barwy oraz jasności
  int MinValue, MaxValue;					// Wartości max i min jakie może przyjąc Value
  int RedCorrection, 						// Korekcja bieli dla kanałów R G B / 0 - 100% / domyślnie 100%
  	  GreenCorrection, BlueCorrection;

  int PCA_Channel_R, PCA_Channel_G,			// Adresy kanałów RGBW modułu PWM
  	  PCA_Channel_B, PCA_Channel_W;
};


/* Function prototypes -----------------------------------------------*/

METHOD_ERROR LED_SwitchOn(struct LED *Object, int Time, int Ramp);
METHOD_ERROR LED_SwitchOff(struct LED *Object, int Time, int Ramp);
METHOD_ERROR LED_Switch(struct LED *Object, int Time, int Ramp);

METHOD_ERROR LED_SetMaxValue(struct LED *Object, int Value); //0-100
METHOD_ERROR LED_SetMinValue(struct LED *Object, int Value); //0-100

//ramp default or time 0-15000ms
 //Value 0-1
METHOD_ERROR LED_SetValue(struct LED *Object, int Value, int Ramp);
METHOD_ERROR LED_SetSaturation(struct LED *Object, int Value, int Ramp);
//Value 0-360
METHOD_ERROR LED_SetHue(struct LED *Object, int Value, int Ramp);

//Value 0-255
METHOD_ERROR LED_SetRedValue(struct LED *Object, int Value, int Ramp);
METHOD_ERROR LED_SetGreenValue(struct LED *Object, int Value, int Ramp);
METHOD_ERROR LED_SetBlueValue(struct LED *Object, int Value, int Ramp);
METHOD_ERROR LED_SetWhiteValue(struct LED *Object, int Value, int Ramp);

METHOD_ERROR LED_SetRGBValue(struct LED *Object, int Value, int Ramp); //HEX

METHOD_ERROR LED_SetRampTime(struct LED *Object, int RampTime);


METHOD_ERROR LED_HoldValue(struct LED *Object, int Ramp); //ms
METHOD_ERROR LED_HoldHue(struct LED *Object, int Ramp);
METHOD_ERROR LED_HoldRedValue(struct LED *Object, int Ramp);//0-10000
METHOD_ERROR LED_HoldGreenValue(struct LED *Object, int Ramp);
METHOD_ERROR LED_HoldBlueValue(struct LED *Object, int Ramp);
METHOD_ERROR LED_HoldWhiteValue(struct LED *Object, int Ramp);

#endif
