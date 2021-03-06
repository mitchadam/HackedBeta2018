#include<Wire.h>

#include <SPI.h> // Not actually used but needed to compile


const int MPU_address = 0x68; // I2C 7-bit address AD0 pin plugged into ground
int16_t AcX,AcY,AcZ;

/*
 * Accelerometer Pins:
 * INT - interrupt pin D2
 * AD0 - Either GND or no connection
 * XCL - 
 * XDA - 
 * SDA - A4
 * SCL - A5
 * GND - GND
 * VCC - 5v
 * 
 * Transmitter Pins:
 * Data - D12
 * GND - GND
 * VCC - 5V
 */

void setup() {

Serial.begin(9600);   // Debugging only
    

  
  Wire.begin(); // join the Arduino and MPU together 
  Wire.beginTransmission(MPU_address); // begin transmission to slave device
  Wire.write(0x6B); // writes bytes to device PWR_MGMT_1 register
  Wire.write(0);  // sends 0 to wake up MPU-6050 writing to PWR_MGMT_1 register
  Wire.endTransmission(true);
  
  // Changes the full scale range of the MPU 6050 for appropriate sensitivity
  Wire.beginTransmission(MPU_address);
  Wire.write(0x1C);
  Wire.write(1);
  Wire.endTransmission(true);
  Serial.begin(9600);
  
}

void loop() {
  int16_t inputVariable[6];
  int16_t Tmp;

    Wire.beginTransmission(MPU_address);
    Wire.write(0x3B); // starting with regoster 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_address,14,true); //request 14 registers, 3 Ac, 3 Gyro, 1 temp each 2 registers
     // read bits 15-0 in groups of 8 bits (bits 15-8 shifted over 8 bits)
     // read Accelerometer values
    inputVariable[0] = Wire.read()<<8|Wire.read(); //AcX
    inputVariable[1] = Wire.read()<<8|Wire.read(); //AcY
    inputVariable[2] = Wire.read()<<8|Wire.read(); //AcZ
    Serial.println("start");
    //Serial.print("AcX = "); 
    Serial.println(inputVariable[0]);
    //Serial.print("AcY = "); 
    Serial.println(inputVariable[1]);
    //Serial.print("AcZ = "); 
    Serial.println(inputVariable[2]);

      
    Tmp = Wire.read()<<8|Wire.read();
    inputVariable[3] = Wire.read()<<8|Wire.read(); // GyX
    inputVariable[4] = Wire.read()<<8|Wire.read(); // GyY
    inputVariable[5] = Wire.read()<<8|Wire.read(); // GyZ
    //Serial.print("GyX = "); 
    Serial.println(inputVariable[3]);
    //Serial.print("GyY = "); 
    Serial.println(inputVariable[4]);
    //Serial.print("GyZ = "); 
    Serial.println(inputVariable[5]);
    Serial.println("end");






    delay(50);
}
