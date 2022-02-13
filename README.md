# STM32F103_Arduino_IMU_GPS

# Overview
![gps](https://user-images.githubusercontent.com/32397445/153751849-084d451a-b3e3-4370-98fb-b5484dbe0f21.jpg)

In this project we will Measure angles and GPS position and velocity using MPU6050 & STM32F103C8 Microcontroller. This can be done by simply interfacing MPU6050 6 axis Gyro/Accelerometer Sensor with STM32. The Accelerometer sends X, Y, and Z acceleration forces. We need to convert the forces into X, Y, Z 3D angle to determine the 3D Orientation of the sensor. 
The gyroscope measures rotational velocity or rate of change of the angular position over time, along the X, Y and Z-axis. It uses MEMS technology and the Coriolis Effect for measuring. The outputs of the gyroscope are in degrees per second, so in order to get the angular position, we just need to integrate the angular velocity.

# MPU6050 Pinout
The MPU-6050 module has 8 pins:
![mpu-6050](https://user-images.githubusercontent.com/32397445/153751934-f2351d8c-3d07-40a5-b1dc-27d873782b03.jpg)

INT: Interrupt digital output pin.
AD0: I2C Slave Address LSB pin. This is 0th bit in 7-bit slave address of device. If connected to VCC then it is read as logic one and slave address changes.
XCL: Auxiliary Serial Clock pin. This pin is used to connect other I2C interface enabled sensors SCL pin to MPU-6050.
XDA: Auxiliary Serial Data pin. This pin is used to connect other I2C interface enabled sensors SDA pin to MPU-6050.
SCL: Serial Clock pin. Connect this pin to microcontrollers SCL pin.
SDA: Serial Data pin. Connect this pin to microcontrollers SDA pin.
GND: Ground pin. Connect this pin to ground connection.
VCC: Power supply pin. Connect this pin to +5V DC supply.


# Ubx GPS Protocol
UBX Protocol Key Features
u-blox GNSS receivers use a u-blox proprietary protocol to transmit GNSS data to a host computer. This protocol has the following key features:
• Compact - uses 8 Bit Binary Data.
• Checksum Protected - uses a low-overhead checksum algorithm
• Modular - uses a 2-stage message identifier (Class- and Message ID)
![image](https://user-images.githubusercontent.com/32397445/153752263-8f42d25f-e5c8-48c8-85fe-199f8a0fb761.png)
  
Every Message starts with 2 Bytes: 0xB5 0x62
• A 1 Byte Class Field follows. The Class defines the basic subset of the message
• A 1 Byte ID Field defines the message that is to follow
• A 2 Byte Length Field is following. Length is defined as being the length of the payload, only. It does not
include Sync Chars, Length Field, Class, ID or CRC fields. The number format of the length field is an
unsigned 16-Bit integer in Little Endian Format.
• The Payload is a variable length field.
• CK_A and CK_B is a 16 Bit checksum.


# Pin out of STM32F103C8

STM32F103C8 (BLUE PILL) USART serial communication ports are shown in the pin out image below. These are blue coloured having (PA9-TX1, PA10- RX1, PA2-TX2, PA3- RX2, PB10-TX3, PB11- RX3). It has three such communication channels.
![STM32-Pin-Details_0](https://user-images.githubusercontent.com/32397445/153751808-bf4df817-dbc8-4e2c-94fe-d8a7d34719e9.png)
