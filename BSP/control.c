#include "control.h"

bool Key_Flag=0;

extern RC_Ctl_t RC_Ctl;

/**
  * @brief  重启CPU
	  SHIFT+CTRL+B:重启单片机
  * @param  void
  * @retval void
  */
void Reset_System_CPU(void)
{
	if((RC_Ctl.key.v & 0x10) == KEY_PRESSED_OFFSET_SHIFT && (RC_Ctl.key.v & 0x20) == KEY_PRESSED_OFFSET_CTRL && (RC_Ctl.key.v & 0x8000) == KEY_PRESSED_OFFSET_B)
	{
		delay_ms(1);
		//reset CPU
		__set_FAULTMASK(1);
		NVIC_SystemReset();
	}
}


/**
  * @brief  获取系统模式
  * @param  void
  * @retval void
  */
void Get_SystemMode(void)	
{
   Reset_System_CPU();
		
  if(RC_Ctl.rc.s2 == RC_SW_UP)
	{
		Key_Flag = 1;	
	}
	else if(RC_Ctl.rc.s2 != RC_SW_UP)
	{
		Key_Flag = 0;		
	}
}



