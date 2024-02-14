#ifndef _CLU_H_
#define _CLU_H_

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#include "../Smarthome/Classes/DIMM/DIMM.h"
#include "../Smarthome/Classes/DOUT/DOUT.h"
#include "../Smarthome/Classes/DIN/DIN.h"
#include "../Smarthome/Classes/LED/LED.h"

void CLUTask(void const * argument);

#endif /* INC_TCPSERVER_H_ */
