/**
  ******************************************************************************
  * File Name          : logger.c
  * Description        : logger
  ******************************************************************************
  *				TO DO
  *
  ******************************************************************************
  */
#include "lwip/opt.h"
#include "lwip/api.h"
#include "lwip/sys.h"

#include "string.h"

#include "../TCPserver/tcpserver.h"
#include "logger.h"

char msg[100];
char smsg[100];
extern struct netconn newconn;

void AddToLog(char msg[], LOGGER_TYPE type){
	//int len = 1;//sprintf (smsg, "");
	//netconn_write(newconn, msg, len, NETCONN_COPY);
}
