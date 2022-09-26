# 弹仓锁功能需求

## 一. 硬件相关

### 1. 主控及外设
- 主控：STM32F051C8T6
- 数码管：Aip650
- 压力传感器：HX711
- 通讯接口：RS485
- 状态指示灯：红绿双色灯

### 2. 相关引脚定义
- RS485引脚定义
  - CTS：PA11
  - RTS：PA12
  - TX：PA10
  - RX：PA9
- 压力传感器引脚定义
  - DOUT：PB3
  - SCK：PB4
- 数码管引脚定义
  - DATA：PB9
  - STB：PB8
  - SCK：PB7
- 开锁和锁状态检测
  - 开锁：PB1, H：开锁，持续时间不能超过250ms，L：关锁
  - 锁状态：PB0，H：关锁状态，L：开锁状态
- 状态指示灯
  - 红灯：PA1，H：灭，L：亮
  - 绿灯：PA0，H：灭，L：亮
- DEBUG
  - TX：PA2
  - RX：PA3
  
## 二. 软件模块

1. 开锁及锁状态检测
   > 接收到开锁指令时，检测到锁处于关锁状态时，执行开锁动作，当检测到锁处于开锁状态，停止开锁，且开锁动作最多执行250Ms，然后关锁
2. 数码管
   > 显示子弹数量，子弹数量由上位机提供
3. 称重
   > 重量由压力传感器计算而得，当接收到查询重量指令时，上传给上位机
4. 指示灯
   > 锁处于开锁状态，显示绿灯；锁处于关锁状态，显示红灯；开关锁时，指示灯闪烁，闪烁与否由上位机设置
5. RS485
   > 串口指令
  
