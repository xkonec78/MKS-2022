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
#include "main.h"

void sct_init (void)
{
	sct_led(0);
}

void sct_led(uint32_t value)
{
	for(uint16_t j = 0 ; j < 32; j++){
		HAL_GPIO_WritePin(sct_sdi_GPIO_Port,sct_sdi_Pin,value & 1);
			value >>= 1;												//bit shift to right

		HAL_GPIO_WritePin(sct_clk_GPIO_Port, sct_clk_Pin, 1); 			//rising edge
		HAL_GPIO_WritePin(sct_clk_GPIO_Port, sct_clk_Pin, 0); 			//falling edge
	}

		HAL_GPIO_WritePin(sct_nla_GPIO_Port, sct_nla_Pin, 1); 			//pulse for write 32bit to register
		HAL_GPIO_WritePin(sct_nla_GPIO_Port, sct_nla_Pin, 0);
}

void sct_value(uint16_t value)
{
	static const uint32_t reg_values[3][10]={
			{
				//PCDE--------GFAB @ DIS1
				0b0111000000000111 << 16,
				0b0100000000000001 << 16,
				0b0011000000001011 << 16,
				0b0110000000001011 << 16,
				0b0100000000001101 << 16,
				0b0110000000001110 << 16,
				0b0111000000001110 << 16,
				0b0100000000000011 << 16,
				0b0111000000001111 << 16,
				0b0110000000001111 << 16,
			},
			{
				//----PCDEGFAB---- @ DIS2
				0b0000011101110000 << 0,
				0b0000010000010000 << 0,
				0b0000001110110000 << 0,
				0b0000011010110000 << 0,
				0b0000010011010000 << 0,
				0b0000011011100000 << 0,
				0b0000011111100000 << 0,
				0b0000010000110000 << 0,
				0b0000011111110000 << 0,
				0b0000011011110000 << 0,
			},
			{
				//PCDE--------GFAB @ DIS3
				0b0111000000000111 << 0,
				0b0100000000000001 << 0,
				0b0011000000001011 << 0,
				0b0110000000001011 << 0,
				0b0100000000001101 << 0,
				0b0110000000001110 << 0,
				0b0111000000001110 << 0,
				0b0100000000000011 << 0,
				0b0111000000001111 << 0,
				0b0110000000001111 << 0,
			},
	};

uint32_t reg = 0;
reg |= reg_values[0][value / 100 % 10];
reg |= reg_values[1][value / 10 % 10];
reg |= reg_values[2][value / 1 % 10];
sct_led(reg);

}

#endif /* SCT_C_ */
