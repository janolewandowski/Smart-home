/**
  ******************************************************************************
  * File Name          : logger.h
  * Description        : Methods for DIN Class
  ******************************************************************************
  *				TO DO
  *
  ******************************************************************************
  */

#define _TCP_DEBUG                 1

typedef enum {
/** Logger - ACTION. */
  LOG_ACT       	= 0,
/** Logger - EXCEPTION. */
  LOG_EXC           = 1,
/** Logger - INFO. */
  ERROR_INF         = 2,
} LOGGER_TYPE;

void AddToLog(char *string, LOGGER_TYPE type);
void ClearLog();

