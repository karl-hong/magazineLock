#ifndef __COMMON_H__
#define __COMMON_H__
#include <stdint.h>

#define DATABASE_START_ADDR         (0x0800F000)
#define DATABASE_MAGIC              (0xaaaa)

#define DEFAULT_LOCK_DELAY          (30)
#define DEFAULT_LOCK_REPLY_DELAY    (2)
#define DEFAULT_LOCK_LED_FLASH      (0)
#define DEFAULT_LOCK_REPORT         (1)
#define DEFAULT_CALI_VALUE          (0)

#define DELAY_BASE                  (10)//100ms*10 = 1s
#define FLASH_FREQ                  (1)
#define FAULT_DECT                  (5*DELAY_BASE)

#define HX711_FULL_RANGE            (0x800000)
#define HX711_AVDD                  (4514/1000)
#define HX711_GAIN                  (128)

enum {
    CMD_DISABLE = 0,
    CMD_ENABLE,
};

typedef struct {
    uint8_t sendCmdEnable;
    uint16_t sendCmdDelay;
}cmd_setting_t;

typedef struct {
    cmd_setting_t reportStatus;
    cmd_setting_t operateResult;
    cmd_setting_t basicSetting;
    cmd_setting_t ledFlashSetting;
    cmd_setting_t alarmSetting;
    cmd_setting_t reportOperateStatus;
    cmd_setting_t reportWeight;
    cmd_setting_t reportMagazineNum;
    cmd_setting_t clrDisp;
    cmd_setting_t unlockFault;
    cmd_setting_t setCalibrationParamAck;
    cmd_setting_t getCalibrationParamAck;
}cmd_control_t;

typedef struct {
    uint8_t state;
    uint8_t flashOn;
    uint16_t flashCnt;
}led_task_ctrl_t;

typedef struct {
    uint8_t lockDetectState;
    uint8_t lockState;
    uint8_t manulLockState;
    uint8_t lockTaskState;
    uint16_t lockTaskLatencyCnt;
    uint16_t lockReplyDelay;
    uint8_t  ledFlashStatus;
    uint8_t  alarmStatus;
    uint8_t  isReport;
    uint8_t  address;
    uint8_t faultType;
    uint8_t HoldOnDetectEnable;
    uint16_t HoldOnLatencyCnt;
    uint16_t magazineNum;
    uint16_t hx711Delay;
    uint32_t magazineWeight;
    uint32_t lockDelay;
    uint32_t uid0;
    uint32_t uid1;
    uint32_t uid2;
    uint8_t valueK[6];
    uint8_t valueB[6];
    cmd_control_t cmdControl;
    led_task_ctrl_t ledTask;
}lock_ctrl_t;

enum {
    LOCK_TASK_STATE_IDLE = 0,
    LOCK_TASK_STATE_UNLOCK,
};

enum {
    LED_TASK_STATE_IDLE = 0,
    LED_TASK_STATE_FLASH,
};

enum {
    LOCK_STATE_UNLOCK = 0,
    LOCK_STATE_LOCK,
};

enum {
	GREEN_LED = 0,
	RED_LED,
};

enum {
	LED_ON = 0,
	LED_OFF,
};


typedef struct {
    uint16_t magic;
    uint16_t address;
    uint16_t isReport;
    uint16_t ledFlash;
    uint16_t lockDelayLow;
    uint16_t lockDelayHigh;
    uint16_t lockReplyDelay;
    uint16_t alarmStatus;
    uint8_t valueK[6];
    uint8_t valueB[6];
}database_t;


extern lock_ctrl_t lock;

#endif
