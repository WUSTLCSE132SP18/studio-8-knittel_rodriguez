
#include <SparkFun_MMA8452Q.h>

MMA8452Q accel;

void setup() {
  Serial.begin(9600);
  accel.init();
}

void loop() {
  if (accel.available()) {
    accel.read();
    printA();
  }
}

void printA() {
  Serial.print(cx());
  Serial.print("\t");
  Serial.print(cy());
  Serial.print("\t");
  Serial.println(cz());
}

float x() {
  return accel.x;
}

float y() {
  return accel.y;
}

float z() {
  return accel.z;
}

float cx() {
  return accel.cx;
}

float cy() {
  return accel.cy;
}

float cz() {
  return accel.cz;
}



