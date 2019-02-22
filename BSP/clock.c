#include <clock.h>

//引脚初始化
void A_GPIO_Init(GPIO_TypeDef* GPIOx, uint16_t Pin)
{
	GPIO_InitTypeDef gpio;	
	if(GPIOx == GPIOA)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	}
	else if(GPIOx == GPIOB)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	}
	else if(GPIOx == GPIOC)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	}
	
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;	
	gpio.GPIO_Mode = GPIO_Mode_OUT;										
	gpio.GPIO_Pin = Pin;  		
	GPIO_Init(GPIOx,&gpio);	
	GPIO_ResetBits(GPIOx,Pin);
}


/********************************************************灯条0码1码时序**********************************************************/
//第一块装甲板：装甲板：PA9;点阵：PA8;灯条：PA7
float i0=0,j0=0;
void Code0_RGB_bulingbuling_BLUE(GPIO_TypeDef* GPIOx,uint16_t IO)
{
		for(i0=1;i0<=1;i0++) 
		{
				GPIO_SetBits(GPIOx,IO);
				__nop();	                            //0编码的时候高电平给300ns 低电平给875ns   
		}	
		for(i0=0;i0<=3;i0++)  // 146+50
		{
				GPIO_ResetBits(GPIOx,IO);
				__nop();
		}
}

void Code1_RGB_bulingbuling_BLUE(GPIO_TypeDef* GPIOx,uint16_t IO)
{
	for(j0=0;j0<=3;j0++) 
	{
			GPIO_SetBits(GPIOx,IO);
			__nop();	                            //1编码的时候高电平给875ns 低电平给300ns   
	}		
	for(j0=1;j0<=1;j0++)  
	{
			GPIO_ResetBits(GPIOx,IO);
			__nop();
	}	
}

float i=0,j=0;
float debug0=1.5,debug1=5;
void Code0_RGB_bulingbuling_RED(GPIO_TypeDef* GPIOx,uint16_t IO)
{
	for(i=1;i<=debug0;i++) 
	{
		 GPIO_SetBits(GPIOx,IO);
		 __nop();	                            //0编码的时候高电平给300ns 低电平给875ns   
	}	

 for(i=0;i<=debug1;i++)  // 146+50
	{
		GPIO_ResetBits(GPIOx,IO);
		__nop();
	}
}



float debug3=2,debug4=1;
void Code1_RGB_bulingbuling_RED(GPIO_TypeDef* GPIOx,uint16_t IO)
{
	for(j=0;j<=debug3;j++) 
	{
		 GPIO_SetBits(GPIOx,IO);	
	   __nop();	                            //1编码的时候高电平给875ns 低电平给300ns   
	}
 for(j=1;j<=debug4;j++)  
	{
		GPIO_ResetBits(GPIOx,IO);
		__nop();
	}
}



void Code0_RED_Off(GPIO_TypeDef* GPIOx,uint16_t IO)
{
	for(i=1;i<=debug0;i++) 
	{
		 GPIO_SetBits(GPIOx,IO);
		 __nop();	                            //0编码的时候高电平给300ns 低电平给875ns   
	}	

 for(i=0;i<=(debug1+250);i++)  // 146+50
	{
		GPIO_ResetBits(GPIOx,IO);
		__nop();
	}
}

void Code0_BLUE_Off(GPIO_TypeDef* GPIOx,uint16_t IO)
{
		for(i0=1;i0<=1;i0++) 
		{
				GPIO_SetBits(GPIOx,IO);
				__nop();	                            //0编码的时候高电平给300ns 低电平给875ns   
		}	
		for(i0=0;i0<=3;i0++)  // 146+50
		{
				GPIO_ResetBits(GPIOx,IO);
				__nop();
		}
}


