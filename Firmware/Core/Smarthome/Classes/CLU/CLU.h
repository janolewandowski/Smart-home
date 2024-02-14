/**
  ******************************************************************************
  * File Name          : CLU.h
  * Description        : DIN Class
  ******************************************************************************
  *
  *			TODO
  *		ROLLER_SHUTTER
  *		ANALOG_IN
  *		PANEL BUTTON
  *		PANEL PAGE
  *		PANEL TEMP
  *		PANELSENSLIGHT
  *		Thermostat
  *		Timer
  *		SKRYPTY
  *		KALENDARZ CRON
  *
  ******************************************************************************
  */
#ifndef _CLU_H
#define _CLU_H

#include "../inc/gpio.h"

/* Classes of objects -----------------------------------------------*/
struct CLU {
//	Uptime Czas pracy urządzenia od ostatniego resetu (w sekundach)
//	Log Wewnętrzny log urządzenia
//	State Stan urządzenia (lista stanów)
//	IsLocalPower True - jeżeli zasilany lokalnie, false - jeżeli zasilany z magistrali systemowej
//	Date Zwraca aktualną datę
//	Time Zwraca aktualny czas (hh:mm:dd)
//	Day Zwraca numer bieżącego dnia miesiąca
//	Month Zwraca numer bieżącego miesiąca
//	Year Zwraca numer bieżącego roku
//	DayOfWeek Zwraca numer bieżącego dnia tygodnia (0=niedziela)
//	Hour Zwraca aktualną godzinę (bez minut i sekund)
//	Minute Zwraca aktualną liczbę minut od ostatniej pełnej godziny
//	UnixTime Zwraca aktualny uniksowy znacznik czasu
//	FirmwareVersion Informacja na temat bieżącego oprogramowania CLU
};



/* Error's list -----------------------------------------------*/
typedef enum {
/** No error, everything OK. */
  ERROR_OK        	= 0,
/** Error, cannot be changed to the same value. */
  ERROR_CBC         = -1,
/** Error, no specified ID found. */
  ERROR_NOID        = -2,
  /** Error, PCA Module not responding. */
  ERROR_PCA       	= -3,
  /** Error, no . */
  ERROR_TIMEOUT     = -4,
} METHOD_ERROR;


/* Function prototypes -----------------------------------------------*/
METHOD_ERROR CPU_Init();
void CLU_process();


#endif
