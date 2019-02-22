#ifndef __CLOCK_H
#define __CLOCK_H

#include <system.h>

void A_GPIO_Init(GPIO_TypeDef* GPIOx, uint16_t Pin);

void Code0_RGB_bulingbuling_BLUE(GPIO_TypeDef* GPIOx,uint16_t IO);
void Code1_RGB_bulingbuling_BLUE(GPIO_TypeDef* GPIOx,uint16_t IO);

void Code0_RGB_bulingbuling_RED(GPIO_TypeDef* GPIOx,uint16_t IO);
void Code1_RGB_bulingbuling_RED(GPIO_TypeDef* GPIOx,uint16_t IO);
	
void Code0_RED_Off(GPIO_TypeDef* GPIOx,uint16_t IO);
void Code0_BLUE_Off(GPIO_TypeDef* GPIOx,uint16_t IO);


#endif


