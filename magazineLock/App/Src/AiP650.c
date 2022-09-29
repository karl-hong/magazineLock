#include "AIP650.h"
#include "common.h"


/** Private variables --------------------------------------------------------*/
uint8_t DispNum[]={
	0x3F,//0
	0x06,//1
	0x5B,//2
	0x4F,//3
	0x66,//4
	0x6D,//5
	0x7D,//6
	0x07,//7
	0x7F,//8
	0x6F,//9
	0x77,//a
	0x7C,//b
	0x39,//c
	0x5E,//d
	0x79,//e
	0x71//f
};
/** Private function prototypes ----------------------------------------------*/
static void SDA_Output(void);
static void SDA_Input(void);
//static void SCL_Input(void);
static void I2C_Start(void);
static void I2C_Stop(void);
static void I2C_Wait_Ack(void);
static void I2C_Ack(void);
static void I2C_Send_Byte(uint8_t data);
static uint8_t I2C_Read_Byte();


void delay_us(uint32_t nus)
{
    uint32_t Delay = nus;
    do{
        __NOP();
    }while (Delay --);
}

 /**
	******************************************************************
	* @brief   模拟I2C 数据脚配置为输出模式
	* @param   [in]None
	* @retval  None
	* @author  aron566
	* @version V1.0
	* @date    2020-5-18
	******************************************************************
	*/
static void SDA_Output(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = Disp_Dat_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(Disp_Dat_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : AIP_SCL_Pin */
	GPIO_InitStruct.Pin = Dsip_Sck_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(Dsip_Sck_GPIO_Port, &GPIO_InitStruct);
}
 
 /**
	******************************************************************
	* @brief   模拟I2C 数据脚配置为输入模式
	* @param   [in]None
	* @retval  None
	* @author  aron566
	* @version V1.0
	* @date    2020-5-18
	******************************************************************
	*/
static void SDA_Input(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/*Configure GPIO pin : AIP_SDA_Pin */
	GPIO_InitStruct.Pin = Disp_Dat_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(Disp_Dat_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin Output Level */
//	HAL_GPIO_WritePin(AIP_SCL_GPIO_Port, AIP_SCL_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin : AIP_SCL_Pin */
	GPIO_InitStruct.Pin = Dsip_Sck_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(Dsip_Sck_GPIO_Port, &GPIO_InitStruct);
}

/**
  ******************************************************************
  * @brief   模拟I2C发出起始信号
  * @param   [in]None
  * @retval  None
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
static void I2C_Start(void)
{
	SDA_Output();
	SDA_Dout_HIGH();
	SCL_Dout_HIGH();
	delay_us(TIME_UINT);
	SDA_Dout_LOW();
	delay_us(TIME_UINT);
}
 
/**
  ******************************************************************
  * @brief   模拟I2C发出停止信号
  * @param   [in]None
  * @retval  None
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
static void I2C_Stop(void)
{
	SDA_Output();
	SCL_Dout_LOW();
	delay_us(TIME_UINT);
	SDA_Dout_LOW();
	delay_us(TIME_UINT);

	SCL_Dout_HIGH();
	delay_us(TIME_UINT);
	SDA_Dout_HIGH();
	delay_us(TIME_UINT);
}
 
/**
  ******************************************************************
  * @brief   模拟I2C等待应答
  * @param   [in]None
  * @retval  None
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
static void I2C_Wait_Ack(void)
{
	uint8_t i = 1;
	SDA_Input();

	SCL_Dout_LOW();
	delay_us(TIME_UINT);
	SCL_Dout_HIGH();

	while(SDA_Data_IN() && i <= 10) {
		i++;
	}

	SDA_Dout_HIGH();
	delay_us(TIME_UINT);
	SCL_Dout_LOW();//时钟输出0
	SDA_Output();
	delay_us(TIME_UINT);

}
 
/**
  ******************************************************************
  * @brief   模拟I2C应答
  * @param   [in]None
  * @retval  None
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
static void I2C_Ack(void)
{

	SCL_Dout_LOW();
	delay_us(TIME_UINT);

	SDA_Input();
	SCL_Dout_HIGH();

	while(SDA_Data_IN());
	SDA_Output();

	delay_us(TIME_UINT);
	SCL_Dout_LOW();
	delay_us(TIME_UINT);


}
 
/**
  ******************************************************************
  * @brief   模拟I2C不应答
  * @param   [in]None
  * @retval  None
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
//static void I2C_NAck(void)
//{
//	SCL_Dout_LOW();
//	delay_us(TIME_UINT);
//	SDA_Output();
//	SDA_Dout_HIGH();
//	delay_us(TIME_UINT);
//	SCL_Dout_HIGH();
//	delay_us(TIME_UINT);
//	SCL_Dout_LOW();
//}

/**
  ******************************************************************
  * @brief   模拟I2C发送一个字节
  * @param   [in]txd 发送的字节
  * @retval  None
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
static void I2C_Send_Byte(uint8_t data)
{
	//拉低时钟开始数据传输
	SDA_Output();
	for(uint8_t t = 0; t < 8; t++) {
		SCL_Dout_LOW();
		delay_us(TIME_UINT);
		SDA_Write(data & 0x80);
		delay_us(TIME_UINT);
		SCL_Dout_HIGH();
		data <<= 1;
		delay_us(TIME_UINT);
	}
	I2C_Ack();
} 	    

/**
  ******************************************************************
  * @brief   模拟I2C读取一个字节 
  * @param   [in]ack ack=1时，发送ACK，ack=0，发送nACK 
  * @retval  读取到的字节
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
static uint8_t I2C_Read_Byte()
{
	uint8_t receive = 0;
	//SDA设置为输入
	SDA_Input();

	for(uint8_t i = 0;  i< 8; i++ ) {
		SCL_Dout_HIGH();
		delay_us(TIME_UINT);
		receive<<=1;
		receive |= SDA_Data_IN();
		SCL_Dout_LOW();
		delay_us(TIME_UINT);
	}

	SDA_Output();

	SDA_Dout_HIGH();
	SCL_Dout_HIGH();
	delay_us(TIME_UINT);
	SCL_Dout_LOW();
	delay_us(TIME_UINT);
  
	return receive;
}

void sendFullCmd(uint8_t adress, uint8_t data) {
	I2C_Start();
	I2C_Send_Byte(adress);
	I2C_Send_Byte(data);
	I2C_Stop();

}

//without   decimal point
//  0     1    2    3   4    5    6    7    8    9    a    b    c     d   e    f     
//{0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

//with   decimal point
//  0     1    2    3   4    5    6    7    8    9    a    b    c     d   e    f   
//{0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,0xf7,0xfc,0xb9,0xde,0xf9,0xf1};

#define TIME 0

#define POINT 0x80
/**
  ******************************************************************
  * @brief   模拟I2C初始化
  * @param   [in]None
  * @retval  None
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
void AIP650Init(void) {
	uint32_t magazineNum = lock.magazineNum;
	uint8_t dispN0;
	uint8_t dispN1;
	uint8_t dispN2;
	uint8_t dispN3;
	dispN0 = magazineNum / 1000;
	dispN1 = magazineNum / 100 % 10;
	dispN2 = magazineNum / 10 % 10;
	dispN3 = magazineNum % 10;
	
	if(dispN0 >= 16) dispN0 = 15;
	if(dispN1 >= 16) dispN1 = 15;
	if(dispN2 >= 16) dispN2 = 15;
	if(dispN3 >= 16) dispN3 = 15;
	
	sendFullCmd(0x48, 0x51);
	sendFullCmd(0x68, DispNum[dispN0]);
	sendFullCmd(0x6A, DispNum[dispN1]);
	sendFullCmd(0x6C, DispNum[dispN2]);
	sendFullCmd(0x6E, DispNum[dispN3]);
}

void AIP650Task(void)
{
	static uint32_t u32MagazineNum = 0;
	uint8_t dispN0;
	uint8_t dispN1;
	uint8_t dispN2;
	uint8_t dispN3;
	
	if(u32MagazineNum != lock.magazineNum){
		u32MagazineNum = lock.magazineNum;
		dispN0 = u32MagazineNum / 1000;
		dispN1 = u32MagazineNum / 100 % 10;
		dispN2 = u32MagazineNum / 10 % 10;
		dispN3 = u32MagazineNum % 10;
		
		if(dispN0 >= 16) dispN0 = 15;
		if(dispN1 >= 16) dispN1 = 15;
		if(dispN2 >= 16) dispN2 = 15;
		if(dispN3 >= 16) dispN3 = 15;
		
		sendFullCmd(0x48, 0x51);
		sendFullCmd(0x68, DispNum[dispN0]);
		sendFullCmd(0x6A, DispNum[dispN1]);
		sendFullCmd(0x6C, DispNum[dispN2]);
		sendFullCmd(0x6E, DispNum[dispN3]);
	}
}


