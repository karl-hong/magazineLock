#ifndef __LOCK_H__
#define __LOCK_H__
#include "stdint.h"

void app_set_lock_state(uint8_t state);
void Lock_Task(void);

#endif
