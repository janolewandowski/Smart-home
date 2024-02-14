/**
  ******************************************************************************
  * File Name          : LEDRGBW_Methods.h
  * Description        : Methods for LEDRGBW Class
  ******************************************************************************
  *
  *
  ******************************************************************************
  */
#include "LED.h"

/* Function declarations -----------------------------------------------*/

//void HSVtoRGB(float H, float S,float V){
//    if(H>360 || H<0 || S>100 || S<0 || V>100 || V<0){
//        cout<<"The givem HSV values are not in valid range"<<endl;
//        return;
//    }
//    float s = S/100;
//    float v = V/100;
//    float C = s*v;
//    float X = C*(1-abs(fmod(H/60.0, 2)-1));
//    float m = v-C;
//    float r,g,b;
//
//    if(H >= 0 && H < 60){
//        r = C,g = X,b = 0;
//    }
//    else if(H >= 60 && H < 120){
//        r = X,g = C,b = 0;
//    }
//    else if(H >= 120 && H < 180){
//        r = 0,g = C,b = X;
//    }
//    else if(H >= 180 && H < 240){
//        r = 0,g = X,b = C;
//    }
//    else if(H >= 240 && H < 300){
//        r = X,g = 0,b = C;
//    }
//    else{
//        r = C,g = 0,b = X;
//    }
//    int R = (r+m)*255;
//    int G = (g+m)*255;
//    int B = (b+m)*255;
//
//    cout<<"R : "<<R<<endl;
//    cout<<"G : "<<G<<endl;
//    cout<<"B : "<<B<<endl;
//
//}

//Value 0-1
METHOD_ERROR LED_SetValue(struct LED *Object, int Value, int Ramp);
METHOD_ERROR LED_SetSaturation(struct LED *Object, int Value, int Ramp);

//Value 0-360
METHOD_ERROR LED_SetHue(struct LED *Object, int Value, int Ramp);

//Value 0-255
METHOD_ERROR LED_SetRedValue(struct LED *Object, int Value, int Ramp){
	if (Object->RedValue == Value) return ERROR_CBC;

	if (PCA9685_SetPwm(Object->PCA_Channel_R, 0, Value*16)) return ERROR_PCA;
	Object->RedValue = Value;
	OnValueChange(Object->ID);
	return ERROR_OK;
}
METHOD_ERROR LED_SetGreenValue(struct LED *Object, int Value, int Ramp){
	if (Object->GreenValue == Value) return ERROR_CBC;

	if (PCA9685_SetPwm(Object->PCA_Channel_G, 0, Value*16)) return ERROR_PCA;
	Object->GreenValue = Value;
	OnValueChange(Object->ID);
	return ERROR_OK;
}
METHOD_ERROR LED_SetBlueValue(struct LED *Object, int Value, int Ramp){
	if (Object->BlueValue == Value) return ERROR_CBC;

	if (PCA9685_SetPwm(Object->PCA_Channel_B, 0, Value*16)) return ERROR_PCA;
	Object->BlueValue = Value;
	OnValueChange(Object->ID);
	return ERROR_OK;
}
METHOD_ERROR LED_SetWhiteValue(struct LED *Object, int Value, int Ramp){
	if (Object->WhiteValue == Value) return ERROR_CBC;

	if (PCA9685_SetPwm(Object->PCA_Channel_W, 0, Value*16)) return ERROR_PCA;
	Object->WhiteValue = Value;
	OnValueChange(Object->ID);
	return ERROR_OK;
}

METHOD_ERROR LED_SetRGBValue(struct LED *Object, int Value, int Ramp); //HEX

METHOD_ERROR LED_HoldValue(struct LED *Object, int Ramp); //ms
METHOD_ERROR LED_HoldHue(struct LED *Object, int Ramp);

METHOD_ERROR LED_SwitchOn(struct LED *Object, int Time, int Ramp){
	if (Object->Value == 1) return ERROR_CBC;

	if (PCA9685_SetPwm(Object->PCA_Channel_W, 0, Object->RedValue*16)) return ERROR_PCA;
	if (PCA9685_SetPwm(Object->PCA_Channel_W, 0, Object->GreenValue*16)) return ERROR_PCA;
	if (PCA9685_SetPwm(Object->PCA_Channel_W, 0, Object->BlueValue*16)) return ERROR_PCA;
	if (PCA9685_SetPwm(Object->PCA_Channel_W, 0, Object->WhiteValue*16)) return ERROR_PCA;
	Object->Value = 1;
	OnValueChange(Object->ID);
	return ERROR_OK;
}

METHOD_ERROR LED_SwitchOff(struct LED *Object, int Time, int Ramp){
	if (Object->Value == 0) return ERROR_CBC;

	if (PCA9685_SetPwm(Object->PCA_Channel_W, 4095, 0)) return ERROR_PCA;
	if (PCA9685_SetPwm(Object->PCA_Channel_W, 4095, 0)) return ERROR_PCA;
	if (PCA9685_SetPwm(Object->PCA_Channel_W, 4095, 0)) return ERROR_PCA;
	if (PCA9685_SetPwm(Object->PCA_Channel_W, 4095, 0)) return ERROR_PCA;
	Object->Value = 0;
	OnValueChange(Object->ID);
	return ERROR_OK;
}

METHOD_ERROR LED_Switch(struct LED *Object, int Time, int Ramp){
	METHOD_ERROR ERROR_VALUE;
	if (Object->Value){
		ERROR_VALUE = LED_SwitchOff(Object, Time, Ramp);
	}else {
		ERROR_VALUE = LED_SwitchOn(Object, Time, Ramp);
	}
	return ERROR_VALUE;
}

METHOD_ERROR LED_SetRampTime(struct LED *Object, int RampTime);

METHOD_ERROR LED_SetMaxValue(struct LED *Object, int Value); //0-1
METHOD_ERROR LED_SetMinValue(struct LED *Object, int Value);

METHOD_ERROR LED_HoldRedValue(struct LED *Object, int Ramp);//0-10000
METHOD_ERROR LED_HoldGreenValue(struct LED *Object, int Ramp);
METHOD_ERROR LED_HoldBlueValue(struct LED *Object, int Ramp);
METHOD_ERROR LED_HoldWhiteValue(struct LED *Object, int Ramp);
