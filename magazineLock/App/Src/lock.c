#include "lock.h"
#include "main.h"
#include "common.h"
#include "gpio.h"


void app_set_lock_state(uint8_t state)
{
    if(state == LOCK_STATE_UNLOCK){
        HAL_GPIO_WritePin(Lock_On_GPIO_Port, Lock_On_Pin, GPIO_PIN_SET);
    }else{
        HAL_GPIO_WritePin(Lock_On_GPIO_Port, Lock_On_Pin, GPIO_PIN_RESET);
    }
}

void Lock_Task(void)
{
	static uint8_t oldState = LOCK_TASK_STATE_IDLE;
	switch(lock.lockTaskState){
		case LOCK_TASK_STATE_UNLOCK:{
			if(oldState != LOCK_TASK_STATE_UNLOCK){
				oldState = LOCK_TASK_STATE_UNLOCK;
                app_set_lock_state(LOCK_STATE_UNLOCK);
                lock.lockTaskLatencyCnt = 4;
			}
			break;
		}

		case LOCK_TASK_STATE_IDLE:
		default:{
            if(oldState != LOCK_TASK_STATE_IDLE){
                oldState = LOCK_TASK_STATE_IDLE;
                app_set_lock_state(LOCK_STATE_LOCK);
                lock.lockTaskLatencyCnt = 0;
            }

            break;
        }
	}
}

