/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                           (c) Copyright 1992-1999, Jean J. Labrosse, Weston, FL
*                                           All Rights Reserved
*
*                                           MASTER INCLUDE FILE
*********************************************************************************************************
*/


#include <os_cfg.h>
#include <ucos_ii.h>
#include <stm32f10x.h>
#include "stdio.h"
#include "serial.h"

#include "eeprom.h"
#include "led.h"
#include "timer.h"
#include "adc.h"
#include "st7565.h"


extern OS_EVENT	* spk;
extern OS_EVENT	* lcd;
extern OS_EVENT * time_10;















