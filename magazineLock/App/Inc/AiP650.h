#ifndef _AIP650_H
#define _AIP650_H

#include "stdint.h"
#include "main.h"

/** Private defines ----------------------------------------------------------*/
/**  @name CPU频率 */
#define CPU_FREQUENCY_MHZ 72

#define TIME_UINT 1


// Exported macros-----------------------------------------------------------

#define SDA_Dout_LOW()          HAL_GPIO_WritePin(Disp_Dat_GPIO_Port, Disp_Dat_Pin, GPIO_PIN_RESET) 
#define SDA_Dout_HIGH()         HAL_GPIO_WritePin(Disp_Dat_GPIO_Port, Disp_Dat_Pin, GPIO_PIN_SET)
#define SDA_Data_IN()           HAL_GPIO_ReadPin(Disp_Dat_GPIO_Port,  Disp_Dat_Pin)
#define SCL_Dout_LOW()          HAL_GPIO_WritePin(Dsip_Sck_GPIO_Port, Dsip_Sck_Pin, GPIO_PIN_RESET) 
#define SCL_Dout_HIGH()         HAL_GPIO_WritePin(Dsip_Sck_GPIO_Port, Dsip_Sck_Pin, GPIO_PIN_SET)
#define SCL_Data_IN()           HAL_GPIO_ReadPin(Dsip_Sck_GPIO_Port,  Dsip_Sck_Pin)
#define SDA_Write(XX)           HAL_GPIO_WritePin(Disp_Dat_GPIO_Port, Disp_Dat_Pin, (XX?GPIO_PIN_SET:GPIO_PIN_RESET))


void AIP650Init(void);
void AIP650Task(void);

#endif //_AIP650_H
