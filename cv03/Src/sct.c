/*
 * sct.c
 *
 *  Created on: 12. 10. 2022
 *      Author: xkonec78
 */

#ifndef SCT_C_
#define SCT_C_

#include <stdint.h>
#include "stm32f030x8.h"
#include "sct.h"

#define sct_nla(x) do { if (x) GPIOB->BSRR=(1<<5); else GPIOB->BRR=(1<<5);} while (0)
#define sct_sdi(x) do { if (x) GPIOB->BSRR=(1<<4); else GPIOB->BRR=(1<<4);} while (0)
#define sct_clk(x) do { if (x) GPIOB->BSRR=(1<<3); else GPIOB->BRR=(1<<3);} while (0)
#define sct_noe(x) do { if (x) GPIOB->BSRR=(1<<10); else GPIOB->BRR=(1<<10);} while (0)

void sct_init (void)
{
	RCC->AHBENR  |= RCC_AHBENR_GPIOBEN;
	GPIOB->MODER |=(GPIO_MODER_MODER5_0);
	GPIOB->MODER |=(GPIO_MODER_MODER4_0);
	GPIOB->MODER |=(GPIO_MODER_MODER3_0);
	GPIOB->MODER |=(GPIO_MODER_MODER10_0);

	sct_led(0);
	sct_noe(0);
}

void sct_led(uint32_t value)
{
	for(uint16_t j = 0 ; j < 32; j++){
		sct_sdi(value & 1);
		value >>= 1;				//bit shift to right
		sct_clk(1);				    //rising edge
		sct_clk(0);				    //falling edge
	}
	sct_nla(1);						//pulse for write 32bit to register
	sct_nla(0);
}



#endif /* SCT_C_ */
