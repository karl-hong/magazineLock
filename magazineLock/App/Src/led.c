#include "led.h"
#include "common.h"
#include "gpio.h"


void appSetLedState(uint8_t led, uint8_t state)
{
	switch(led){
		case GREEN_LED:{
			if(state) HAL_GPIO_WritePin(Gled_GPIO_Port, Gled_Pin, GPIO_PIN_SET);
			else	  HAL_GPIO_WritePin(Gled_GPIO_Port, Gled_Pin, GPIO_PIN_RESET);
			break;
		}
		
		case RED_LED:{
			if(state) HAL_GPIO_WritePin(Rled_GPIO_Port, Rled_Pin, GPIO_PIN_SET);
			else	  HAL_GPIO_WritePin(Rled_GPIO_Port, Rled_Pin, GPIO_PIN_RESET);
			break;
		}
		
		default:{
			printf("Error: led %d not found!\r\n", led);
			break;
		}
	}
}

void Led_Task(void)
{
	switch(lock.ledTask.state){
		case LED_TASK_STATE_FLASH:{
			if(lock.ledFlashStatus){
				if(!lock.lockDetectState){
					if(lock.ledTask.flashOn)	appSetLedState(GREEN_LED, LED_ON);
					else						appSetLedState(GREEN_LED, LED_OFF);
					appSetLedState(RED_LED, LED_OFF);
				}else{
					appSetLedState(GREEN_LED, LED_OFF);
					if(lock.ledTask.flashOn)	appSetLedState(RED_LED, LED_ON);
					else						appSetLedState(RED_LED, LED_OFF);
				}
			}else{
				if(!lock.lockDetectState){
					appSetLedState(GREEN_LED, LED_ON);
					appSetLedState(RED_LED, LED_OFF);
				}else{
					appSetLedState(GREEN_LED, LED_OFF);
					appSetLedState(RED_LED, LED_ON);
				}
			}
			break;
		}

		case LED_TASK_STATE_IDLE:{
			if(!lock.lockDetectState){
				appSetLedState(GREEN_LED, LED_ON);
				appSetLedState(RED_LED, LED_OFF);
			}else{
				appSetLedState(GREEN_LED, LED_OFF);
				appSetLedState(RED_LED, LED_ON);
			}
			break;
		}

		default:{
			break;
		}
	}
}


