#include "CLU.h"

#include "../Smarthome/Classes/DIMM/DIMM.h"
#include "../Smarthome/Classes/DOUT/DOUT.h"
#include "../Smarthome/Classes/DIN/DIN.h"
#include "../Smarthome/Classes/LED/LED.h"

#include "../PCA9685/pca9685.h"
#include "../Inc/gpio.h"
#include "../Inc/i2c.h"

struct DOUT LED_ERROR;
struct DOUT LED_OK;

struct DIN IN_1;			//Przedpokoj_Switch
struct DIN IN_2;			//Sypialnia_Switch
struct DIN IN_3;			//Kuchnia_Switch
struct DIN IN_4;			//Lazienka_Switch
struct DIN IN_5;			//Salon_Switch

struct DIMM Kuchnia_1;
struct DIMM Kuchnia_2;

struct DIMM Salon_1;
struct DIMM Salon_2;

struct DIMM Przedpokoj;
struct DIMM Lazienka;
struct DIMM Sypialnia;

struct LED Salon_LED;
struct LED Salon_LED_Biurko;

extern int sem;


void CLUTask(void const * argument)
{
	while (!sem){
		osDelay(50);
	}

Kuchnia_1.PCA_Channel = 12;
Kuchnia_2.PCA_Channel = 13;

Salon_1.PCA_Channel = 8;
Salon_2.PCA_Channel = 9;

Przedpokoj.PCA_Channel = 15;
Lazienka.PCA_Channel = 16;
Sypialnia.PCA_Channel = 17;

Salon_LED.PCA_Channel_R = 5;
Salon_LED.PCA_Channel_G = 4;
Salon_LED.PCA_Channel_B = 6;
Salon_LED.PCA_Channel_W = 7;
//Salon_LED.RedValue = 0;
//Salon_LED.GreenValue = 0;
//Salon_LED.BlueValue = 0;
//Salon_LED.WhiteValue = 0;

Salon_LED_Biurko.PCA_Channel_R = 1;
Salon_LED_Biurko.PCA_Channel_G = 0;
Salon_LED_Biurko.PCA_Channel_B = 2;
Salon_LED_Biurko.PCA_Channel_W = 3;

//Light Kuchnia_LED = {14,0,0};
//Light Sypialnia_Kinkiet = {18,0,0};

//DIMM_SwitchOn(Kuchnia_1,0,0);
//DIMM_SwitchOn(Kuchnia_2,0,0);

IN_1.GPIO_Pin = IN_1_Pin;
IN_1.GPIO_Port = IN_1_GPIO_Port;

IN_2.GPIO_Pin = IN_2_Pin;
IN_2.GPIO_Port = IN_2_GPIO_Port;

IN_3.GPIO_Pin = IN_3_Pin;
IN_3.GPIO_Port = IN_3_GPIO_Port;

IN_4.GPIO_Pin = IN_4_Pin;
IN_4.GPIO_Port = IN_4_GPIO_Port;

IN_5.GPIO_Pin = IN_5_Pin;
IN_5.GPIO_Port = IN_5_GPIO_Port;

SetInertion(&IN_1, 30);
//IN_1.Inertion = 30;
IN_2.Inertion = 30;
IN_3.Inertion = 30;
IN_4.Inertion = 30;
IN_5.Inertion = 30;

LED_OK.GPIO_Pin = LED_OK_Pin;
LED_OK.GPIO_Port = LED_OK_GPIO_Port;
LED_ERROR.GPIO_Pin = LED_ERROR_Pin;
LED_ERROR.GPIO_Port = LED_ERROR_GPIO_Port;

DOUT_Switch(&LED_OK,0);
PCA9685_Init(&hi2c1);
//DIMM_SwitchOn(&Kuchnia_1,0,0);

//LED_SetRedValue(&Salon_LED_Biurko, 255, 0);
//LED_SetGreenValue(&Salon_LED, 255, 0);
//LED_SetBlueValue(&Salon_LED, 255, 0);
//LED_SetWhiteValue(&Salon_LED_Biurko, 255, 0);

  /* Infinite loop */
  for(;;)
  {
	  osDelay(1);
	  switch (DIN_Process(&IN_1)){
	  case SINGLE_PRESS:
		  DIMM_Switch(&Przedpokoj,0,0);
		  DOUT_Switch(&LED_OK,0);
		  break;
	  case LONG_PRESS:
		  DIMM_SwitchOff(&Lazienka, 0, 0);
		  DIMM_SwitchOff(&Kuchnia_1, 0, 0);
		  DIMM_SwitchOff(&Kuchnia_2, 0, 0);
		  DIMM_SwitchOff(&Salon_1, 0, 0);
		  DIMM_SwitchOff(&Salon_2, 0, 0);
		  DIMM_SwitchOff(&Sypialnia, 0, 0);
		  //wait 10s
		  DIMM_SwitchOff(&Przedpokoj, 0, 0);

		  LED_SwitchOff(&Salon_LED, 0, 0);
		  LED_SwitchOff(&Salon_LED_Biurko, 0, 0);
		  break;
	  }

	  switch (DIN_Process(&IN_2)){
	  case SINGLE_PRESS:
		  DIMM_Switch(&Sypialnia,0,0);
		  DOUT_Switch(&LED_OK,0);
		  break;
	  }

	  switch (DIN_Process(&IN_3)){
	  case SINGLE_PRESS:
		  DOUT_Switch(&LED_OK,0);

		  if (Kuchnia_1.Value==0 && Kuchnia_2.Value==1){ // STAN KUCHNIA_1 = 0 KUCHNIA_2 = 1
			  DIMM_SwitchOff(&Kuchnia_2,0,0);
			  break;
		  }

		  if(Kuchnia_2.Value==Kuchnia_1.Value)	// STAN KUCHNIA_x == KUCHNIA_x
		  {
			  DIMM_Switch(&Kuchnia_1,0,0);
			  DIMM_Switch(&Kuchnia_2,0,0);
			  break;
		  }
		  break;

	  case DOUBLE_PRESS:
		  DOUT_Switch(&LED_OK,0);

		  if(Kuchnia_2.Value==0 && Kuchnia_1.Value==0)	// STAN KUCHNIA_x == KUCHNIA_x
		  {
			  DIMM_SwitchOn(&Kuchnia_2,0,0);
			  break;
		  }

		  if (Kuchnia_1.Value==0 && Kuchnia_2.Value==1){ // STAN KUCHNIA_1 = 0 KUCHNIA_2 = 1
			  DIMM_SwitchOff(&Kuchnia_2,0,0);
			  break;
		  }

		  if(Kuchnia_2.Value==1 && Kuchnia_1.Value==1)	// STAN KUCHNIA_x == KUCHNIA_x
		  {
			  DIMM_SwitchOff(&Kuchnia_1,0,0);
			  break;
		  }
		  break;
	  }

	  switch (DIN_Process(&IN_4)){
	  case SINGLE_PRESS:
		  DIMM_Switch(&Lazienka,0,0);
		  DOUT_Switch(&LED_OK,0);
		  break;
	  }

	  switch (DIN_Process(&IN_5)){
	  case SINGLE_PRESS:
		  DIMM_Switch(&Salon_1,0,0);
		  DIMM_Switch(&Salon_2,0,0);
		  DOUT_Switch(&LED_OK,0);
		  break;
	  case DOUBLE_PRESS:
		  Salon_LED.WhiteValue = 200;
		  Salon_LED_Biurko.WhiteValue = 200;
		  LED_Switch(&Salon_LED, 0, 0);
		  LED_Switch(&Salon_LED_Biurko, 0, 0);
		  break;
	  case LONG_PRESS:
		  break;
	  }

  }

}
