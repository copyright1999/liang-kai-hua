#ifndef __CONTROL_H
#define __CONTROL_H

#include "system.h"

void Get_SystemMode(void);
void Reset_System_CPU(void);

enum system_mode
{	
	Error_Mode=0,
	Normal_Mode
};

#endif
