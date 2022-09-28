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

## 三. 通讯协议

1. 单板状态查询指令
   > 请求帧：帧头 + 指令 + 操作码 + 数据长度 + UID + 校验码 + 帧尾  
     应答帧：帧头 + 指令 + 操作码 + 数据长度 + 地址 + 锁状态 + 闪烁状态 + 报警状态 + 是否开启主动上报 + UID + 校验码 + 帧尾
2. 批量开锁指令
   > 请求帧：帧头 + 指令 + 操作码 + 数据长度 + 开/关锁 + 校验码 + 帧尾  
     应答帧：无
3. 单板开锁指令
   > 请求帧：帧头 + 指令 + 操作码 + 数据长度 + 开/关锁 + UID + 校验码 + 帧尾
     应答帧：帧头 + 指令 + 操作码 + 数据长度 + 地址 + 锁状态 + UID + 校验码 + 帧尾
4. 批量基础设置指令
   > 请求帧：帧头 + 指令 + 操作码 + 数据长度 + 是否开启主动上报 + 校验码 + 帧尾 
     应答帧：无
5. 单板基础设置指令
   > 请求帧：帧头 + 指令 + 操作码 + 数据长度 + 地址 + 是否开启主动上报 + UID + 校验码 + 帧尾 
     应答帧：帧头 + 指令 + 操作码 + 数据长度 + 地址 + 是否开启主动上报 + UID + 校验码 + 帧尾
6. 批量指示灯闪烁设置指令
   > 请求帧：帧头 + 指令 + 操作码 + 数据长度 + 是否闪烁当前灯 + 校验码 + 帧尾 
     应答帧：无
7. 单板指示灯闪烁设置指令
   > 请求帧：帧头 + 指令 + 操作码 + 数据长度 + 是否闪烁当前灯 + UID + 校验码 + 帧尾 
     应答帧：帧头 + 指令 + 操作码 + 数据长度 + 地址 + 是否闪烁当前灯 + UID + 校验码 + 帧尾
8. 批量报警清除指令
   > 请求帧：帧头 + 指令 + 操作码 + 数据长度 + 校验码 + 帧尾 
     应答帧：无
9. 单板报警清除指令
   > 请求帧：帧头 + 指令 + 操作码 + 数据长度 + UID + 校验码 + 帧尾 
     应答帧：帧头 + 指令 + 操作码 + 数据长度 + 地址 + 报警状态 + UID + 校验码 + 帧尾
10. 单板获取称重传感器重量值
    > 请求帧：帧头 + 指令 + 操作码 + 数据长度 + UID + 校验码 + 帧尾 
      应答帧：帧头 + 指令 + 操作码 + 数据长度 + 重量值 + UID + 校验码 + 帧尾
11. 单板设置数据管显示内容
    > 请求帧：帧头 + 指令 + 操作码 + 数据长度 + 子弹数量 + UID + 校验码 + 帧尾 
      应答帧：帧头 + 指令 + 操作码 + 数据长度 + 子弹数量 + UID + 校验码 + 帧尾
12. 单板清空数据管显示内容
    > 请求帧：帧头 + 指令 + 操作码 + 数据长度 + UID + 校验码 + 帧尾 
      应答帧：帧头 + 指令 + 操作码 + 数据长度 + UID + 校验码 + 帧尾
13. 批量清空数码管显示内容
    > 请求帧：帧头 + 指令 + 操作码 + 数据长度 + 校验码 + 帧尾 
      应答帧：无
14. 单板手动开/关报警上报
    > 请求帧：帧头 + 指令 + 操作码 + 数据长度 + 地址 + 报警类型 + UID + 校验码 + 帧尾 
      应答帧：无
  
