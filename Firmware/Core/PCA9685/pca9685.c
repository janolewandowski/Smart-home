#include "../Inc/main.h"
#include "../Inc/i2c.h"

#include "pca9685.h"
#include <math.h>
//#include <stdint.h>

I2C_HandleTypeDef *pca9685_i2c;


PCA9685_STATUS PCA9685_SetBit(uint8_t Register, uint8_t Bit, uint8_t Value, PCA9685_DeviceNumber Device)
{
	int Address = 0;
	if (!Device) Address =  PCA9685_ADDRESS;
	if (Device) Address =  PCA9685_ADDRESS2;

	uint8_t tmp;
	if(Value) Value = 1;

	if(HAL_OK != HAL_I2C_Mem_Read(pca9685_i2c, Address, Register, 1, &tmp, 1, 100))
	{
		return PCA9685_ERROR;
	}
	tmp &= ~((1<<PCA9685_MODE1_RESTART_BIT)|(1<<Bit));
	tmp |= (Value&1)<<Bit;

	if(HAL_OK != HAL_I2C_Mem_Write(pca9685_i2c, Address, Register, 1, &tmp, 1, 10))
	{
		return PCA9685_ERROR;
	}

	return PCA9685_OK;
}

PCA9685_STATUS PCA9685_SoftwareReset(void)
{
	uint8_t cmd = 0x6;
	if(HAL_OK == HAL_I2C_Master_Transmit(pca9685_i2c, 0x00, &cmd, 1, 10))
	{
		return PCA9685_OK;
	}
	return PCA9685_ERROR;
}

PCA9685_STATUS PCA9685_SleepMode(uint8_t Enable, PCA9685_DeviceNumber Device)
{
	return PCA9685_SetBit(PCA9685_MODE1, PCA9685_MODE1_SLEEP_BIT, Enable, Device);
}

PCA9685_STATUS PCA9685_RestartMode(uint8_t Enable, PCA9685_DeviceNumber Device)
{

	return PCA9685_SetBit(PCA9685_MODE1, PCA9685_MODE1_RESTART_BIT, Enable, Device);
}

PCA9685_STATUS PCA9685_AutoIncrement(uint8_t Enable, PCA9685_DeviceNumber Device)
{
	return PCA9685_SetBit(PCA9685_MODE1, PCA9685_MODE1_AI_BIT, Enable, Device);
}

PCA9685_STATUS PCA9685_SubaddressRespond(SubaddressBit Subaddress, uint8_t Enable, PCA9685_DeviceNumber Device)
{
	return PCA9685_SetBit(PCA9685_MODE1, Subaddress, Enable, Device);
}

PCA9685_STATUS PCA9685_AllCallRespond(uint8_t Enable, PCA9685_DeviceNumber Device)
{
	return PCA9685_SetBit(PCA9685_MODE1, PCA9685_MODE1_ALCALL_BIT, Enable, Device);
}

//
//	Frequency - Hz value
//
PCA9685_STATUS PCA9685_SetPwmFrequency(uint16_t Frequency, PCA9685_DeviceNumber Device)
{

	int Address = 0;
	if (!Device) Address =  PCA9685_ADDRESS;
	if (Device) Address =  PCA9685_ADDRESS2;

	float PrescalerVal;
	uint8_t Prescale;

	if(Frequency >= 1526)
	{
		Prescale = 0x03;
	}
	else if(Frequency <= 24)
	{
		Prescale = 0xFF;
	}
	else
	{
		PrescalerVal = (25000000 / (4096.0 * (float)Frequency)) - 1;
		Prescale = floor(PrescalerVal + 0.5);
	}

	//
	//	To change the frequency, PCA9685 have to be in Sleep mode.
	//
	PCA9685_SleepMode(1, Device);
	HAL_I2C_Mem_Write(pca9685_i2c, Address, PCA9685_PRESCALE, 1, &Prescale, 1, 10); // Write Prescale value
	PCA9685_SleepMode(0, Device);
	PCA9685_RestartMode(1, Device);
	return PCA9685_OK;
}

PCA9685_STATUS PCA9685_SetPwm(uint8_t Channel, uint16_t OnTime, uint16_t OffTime)
{
	// If selected Channel is >15 then select device no 2.
	int Address = 0;
	if (Channel >= 16) {
		Address =  PCA9685_ADDRESS2;
		Channel = Channel - 16;
	}else{
		Address =  PCA9685_ADDRESS;
	}


	uint8_t RegisterAddress;
	uint8_t Message[4];

	RegisterAddress = PCA9685_LED0_ON_L + (4 * Channel);
	Message[0] = OnTime;// & 0xFF;
	Message[1] = OnTime>>8;
	Message[2] = OffTime;// & 0xFF;
	Message[3] = OffTime>>8;


	if(HAL_OK != HAL_I2C_Mem_Write(pca9685_i2c, Address, RegisterAddress, 1, Message, 4, 100))
		{
			return PCA9685_ERROR;
		}

	return PCA9685_OK;
}


PCA9685_STATUS PCA9685_Init(I2C_HandleTypeDef *hi2c)
{
	pca9685_i2c = hi2c;

	PCA9685_SoftwareReset();

	PCA9685_SetPwmFrequency(10000, FirstDevice);
	PCA9685_AutoIncrement(1, FirstDevice);

	PCA9685_SetPwmFrequency(10000, SecondDevice);
	PCA9685_AutoIncrement(1, SecondDevice);

	return PCA9685_OK;
}
