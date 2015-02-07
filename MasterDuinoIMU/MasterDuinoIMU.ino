#include "Wire.h"

  byte RAxH, RAyH, RAzH, RHeadingH, RGxH, RGyH, RGzH, RAxL, RAyL, RAzL, RHeadingL, RGxL, RGyL, RGzL;
  int ExpectedBytes = 14;
  
  int number = 0;
  
  float RAx, RAy, RAz, RHeading, RGx, RGy, RGz;
  
void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
  ReadIMU();
  Serial.println(number);
  Serial.print("Accel X: "); Serial.print(RAx); Serial.print(" ");
  Serial.print("  \tY: "); Serial.print(RAy);       Serial.print(" ");
  Serial.print("  \tZ: "); Serial.print(RAz);     Serial.println("  \tm/s^2");

  // print out heading
  Serial.print("Heading = "); Serial.print(RHeading); Serial.println(" deg");
  
  // print out gyroscopic data
  Serial.print("Gyro  X: "); Serial.print(RGx); Serial.print(" ");
  Serial.print("  \tY: "); Serial.print(RGy);       Serial.print(" ");
  Serial.print("  \tZ: "); Serial.print(RGz);     Serial.println("  \tdps");

number++;
}

void ReadIMU()
{
  int x = 0;
  byte imuReturn[14];
  
  Wire.requestFrom(0x6F, ExpectedBytes);
while (Wire.available())
{
  for (x; x < ExpectedBytes; x++)
  {
    imuReturn[x] = Wire.read();
  }
  
  RAxH = imuReturn[0];
  RAxL = imuReturn[1];
  RAyH = imuReturn[2];
  RAyL = imuReturn[3];
  RAzH = imuReturn[4];
  RAzL = imuReturn[5];
  RHeadingH = imuReturn[6];
  RHeadingL = imuReturn[7];
  RGxH = imuReturn[8];
  RGxL = imuReturn[9];
  RGyH = imuReturn[10];
  RGyL = imuReturn[11];
  RGzH = imuReturn[12];
  RGzL = imuReturn[13];
}
}

void dataArrange()
{
  RAx = (RAxH + RAxL) / 100;
  RAy = (RAyH + RAyL) / 100;
  RAz = (RAzH + RAzL) / 100;
  RHeading = (RHeadingH + RHeadingL);
  RGx = (RGxH + RGxL) / 100;
  RGy = (RGyH + RGyL) / 100;
  RGz = (RGzH + RGzL) / 100;
}
