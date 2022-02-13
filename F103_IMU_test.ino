#include<Wire.h>
#include <stdlib.h>     /* atof */
#include <stdio.h> 

int16_t AcX, AcY, AcZ, GyX, GyY, GyZ, Tmp;
float Ax, Ay, Az, Gx, Gy, Gz;
float Phi, Theta, Psi, Roll, Pitch, Yaw;
float Lat, Lng, Hgt, Vn, Ve, Vd; // GPS variables
float X, Y, Z, Vx, Vy, Vz;
float Heading;




//................. sample Time.......
float dt = 0.13;
float SmpT;
unsigned long timer = 0;
float timeStep ;

char Buffer[24];
char Ax_c[5];
char Ay_c[5];
char Az_c[5];
float Axx;
//MPU6050 accelgyro;




void setup()
{
  ///******************* GPS Serial Init********************
  /*Serial1.begin(9600);

    // send configuration data in UBX protocol
    for (int i = 0; i < sizeof(UBLOX_INIT); i++) {
    Serial1.write( pgm_read_byte(UBLOX_INIT + i) );
    delay(5); // simulating a 38400baud pace (or less), otherwise commands are not accepted by the device.
    }
  */
  Wire.begin();
    Wire.beginTransmission(0x68);
    Wire.write(0x6B);  // PWR_MGMT_1 register
    Wire.write(0);     // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);

//  //Bypass Mode
//  Wire.beginTransmission(0x68);
//  Wire.write(0x37);
//  Wire.write(0x02);
//  Wire.endTransmission();
//
//  Wire.beginTransmission(0x68);
//  Wire.write(0x6A);
//  Wire.write(0x00);
//  Wire.endTransmission();
//
//  //Disable Sleep Mode
//  Wire.beginTransmission(0x68);
//  Wire.write(0x6B);
//  Wire.write(0x00);
//  Wire.endTransmission(true);
  Serial.begin(115200);
  //Serial3.begin(115200);
  /*
  Serial.println("Initializing I2C devices...");
    //accelgyro.setSleepEnabled(false);
    accelgyro.initialize();
    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");


    // join I2C bus (I2Cdev library doesn't do this automatically)***********
    Wire.begin();
    Serial.println("Initializing I2C devices...");
    accelgyro.setSleepEnabled(false);
    accelgyro.initialize();
    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  */



}



void loop() {

  timer = millis();


  //
    Wire.beginTransmission(0x68);
    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission();
    Wire.requestFrom(0x68, 14, true); // request a total of 14 registers
//  
//  Wire.requestFrom(0x68, 12,  0x3B,  1);

  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  //accelgyro.getMotion6(&AcX, &AcY, &AcZ, &GyX, &GyY, &GyZ);
  Ax = AcX * 9.81 / 16834.0; // m/s^2
  Ay = AcY * 9.81 / 16834.0;
  Az = AcZ * 9.81 / 16834.0;
  Gx = (GyX / 131) * (PI / 180) ; // To rad
  Gy = (GyY / 131) * (PI / 180);
  Gz = (GyZ / 131) * (PI / 180) ;

  Phi = (Phi + Gx * dt) ;   //  rad
  Theta = (Theta + Gy * dt); //  rad
  Psi = (Psi + Gz * dt) ;   //  rad
  Roll = Phi; Pitch = Theta; Yaw = Psi;



  timeStep = (millis() - timer);
  SmpT = timeStep / 1000;
  //dt=SmpT;
  //Serial.println(SmpT, 5); Serial.print("\n");



//  Serial.print("Az = ");  
//  Serial.print(Az); 
//  Serial.print("\t");
//  Serial3.print("Acz = ");  
//  Serial.println(Az);

//  Serial3.print("Roll = ");  Serial3.print(Roll); Serial3.print("\t");
//  Serial3.print("Pitch = ");  Serial3.print(Pitch); Serial3.print("\t");
//  Serial3.print("Yaw = "); 
//  Serial.println(Yaw); 
//
//  Serial3.print("Vx = ");  Serial3.print(Vx); Serial3.print("\t");
//  Serial3.print("Lat = ");  Serial3.println(Lat);

    
int Aax=Ax*100;
int Aay=Ay*100;
int Aaz=Az*100;

//sprintf(Buffer, "%d", Az);
//  sprintf (Buffer, "I,%d,%d,%d,U", Aax,Aay,Aaz);
//  Serial.println(Buffer);

  sprintf (Az_c, "%d", Aaz);
  Serial.println(Az_c);

  //Serial.println(Buffer);
//Serial.print(Ax,2); Serial.print(",");                  
//Serial.print(Ay,2); Serial.print(",");
////Serial.print(Az,2); Serial.println("U");                  
//sprintf(Ax_c, "%2f",Ax);
//sprintf(Ay_c, "%2f",Ay);
//sprintf(Az_c, "%2f",Az);
//Serial.println("I");
//Serial.print(Ax_c);Serial.print(",");Serial.print(Ay_c);Serial.print(",");Serial.println(Az_c);
}
