/* Includes ------------------------------------------------------------------*/
#include "HX711.h"
#include "main.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "common.h"

static uint8_t s_hx711_state = 0;
static uint16_t s_hx711_busy_cnt = 0;

void HX711_task(void)
{
     switch(s_hx711_state){
        case 1:{
            /* check convert complete */
            if(HAL_GPIO_ReadPin(HX711_Dat_GPIO_Port, HX711_Dat_Pin)){
                //printf("HX711 is busy!\r\n");
								s_hx711_busy_cnt ++;
								if(s_hx711_busy_cnt > 1000){
									s_hx711_state = 0;
								}
                return;
            }
            /* HX711 data is ready, goto next state */
            s_hx711_state = 2;
            break;
        }

        case 2:{
            /* read out hx711 data */
            uint32_t data = 0;
            uint8_t i;
            for(i=0;i<24;i++){
                HAL_GPIO_WritePin(HX711_Sck_GPIO_Port, HX711_Sck_Pin, GPIO_PIN_SET);
                data = data<<1;
                HAL_GPIO_WritePin(HX711_Sck_GPIO_Port, HX711_Sck_Pin, GPIO_PIN_RESET);
                if(HAL_GPIO_ReadPin(HX711_Dat_GPIO_Port, HX711_Dat_Pin)){
                    data ++; 
                }
            }

            HAL_GPIO_WritePin(HX711_Sck_GPIO_Port, HX711_Sck_Pin, GPIO_PIN_SET);
            data = data^0x800000;
            HAL_GPIO_WritePin(HX711_Sck_GPIO_Port, HX711_Sck_Pin, GPIO_PIN_RESET);
            /* get hx711 data here */
						lock.magazineWeight = data;
            /* goto next state */
            s_hx711_state = 0;
						lock.hx711Delay = 10;//1s
            break;
        }
        
        case 0:
        default:{
            if(lock.hx711Delay > 0) break;
            HAL_GPIO_WritePin(HX711_Sck_GPIO_Port, HX711_Sck_Pin, GPIO_PIN_RESET);
            s_hx711_state = 1;
						s_hx711_busy_cnt = 0;
            break;
        }
     }
}


