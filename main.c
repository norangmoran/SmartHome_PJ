#include <Servo.h>
char LOCK='N';
Servo DoorLock; //서보모터 제어용 객체생성

void setup() {
  Serial.begin(9600);
  DoorLock.attach(11);
}

void loop() {
  while(Serial.available()) {
  	LockSys(Serial.read());
  }
}
