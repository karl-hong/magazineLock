#ifndef __USER_DATA_H__
#define __USER_DATA_H__
#include <stdint.h>

void onCmdQueryDeviceStatus(uint8_t *data, uint16_t length);

void onCmdSetDeviceStatus(uint8_t *data, uint16_t length, uint8_t ack);

void onCmdModifyDeviceSetting(uint8_t *data, uint16_t length, uint8_t ack);

void onCmdSetLedFlash(uint8_t *data, uint16_t length, uint8_t ack);

void onCmdClrDevAlarmSetting(uint8_t *data, uint16_t length, uint8_t ack);

void onCmdGetWeight(uint8_t *data, uint16_t length);

void onCmdSetDispContent(uint8_t *data, uint16_t length);

void onCmdClrDispContent(uint8_t *data, uint16_t length, uint8_t ack);

void onCmdSetCalibrationParam(uint8_t *data, uint16_t length);

void onCmdGetCalibrationParam(uint8_t *data, uint16_t length);

void onCmdSetDeviceStatusByAddr(uint8_t *data, uint16_t length);

void onCmdSetLedFlashByAddr(uint8_t *data, uint16_t length);

void onCmdClrDevAlarmSettingByAddr(uint8_t *data, uint16_t length);

void onCmdClrDispContentByAddr(uint8_t *data, uint16_t length);

void onCmdSetDispContentByAddr(uint8_t *data, uint16_t length);

void onCmdSetMultiDevsDispContent(uint8_t *data, uint16_t length);

void onReportDeviceStatus(void);

void onReportDeviceOptResult(void);

void onReportSetDeviceResult(void);

void onReportSetLedFlashStatus(void);

void onReportClearDevAlarmSetting(void);

void onReportDevAlarm(uint8_t alarmType);

void onReportWeight(void);

void onReportMagazineNum(void);

void onReportClrDisp(void);

void onReportSetCalibrationParam(void);

void onReportGetCalibrationParam(void);

void user_database_init(void);

void user_database_save(void);

void user_reply_handle(void);

#endif
