#include <Servo.h>
#include <Wire.h>
char LOCK='N';
Servo DoorLock; //서보모터 제어용 객체생성

void setup(){
  Wire.begin();
  
  Serial.begin(9600);
  DoorLock.attach(11);
}

void loop(){
  while(Serial.available()){
  	LockSys(Serial.read());
  }
}
void CallMaster(){ //3회 접속실패시
  LCDPRINT("A Number of Failures","Close for 30 sec..");
  Serial.print("Access fail"); //라즈베리에서 사진촬영,주인에게 메세지전송!
  delay(30000);
  Attempt=0;
  seri='Y';
}
void FaceRecog(int What){
//얼굴인식
}
void LCDPRINT(String A){ //LCD문자출력1
  lcd.begin(16,2);
  lcd.print(A);
}
void LCDPRINT(String A,String B){ //LCD문자출력2
  lcd.begin(16,2);
  lcd.print(A);
  lcd.setCursor(0,1);
  lcd.print(B);
}
void LockSys(char seri){ //도어락 잠금 시스템
  switch(seri){
        case 'A': //비밀번호 통과. 얼굴인식 준비.
          LCDPRINT("Face recognition..","Please See Camera");
          FaceRecog();
          break;
        case 'B': //비밀번호 오류
          Attempt++;
          LCDPRINT("Wrong Password","Attempt: ");
          lcd.print(Attempt);
          delay(500);
          if(Attempt==3){CallMaster();}
          seri='Y';//처음으로 돌아감
          break;
        case 'C': //얼굴인식 오류
          Attempt++;
          LCDPRINT("Face recognition","Fail..");
          delay(500);
          if(Attempt==3){CallMaster();}
          seri='Y'; //처음으로 돌아감
          break;
        case 'D': //개방
          Attempt=0;
          LCDPRINT("Welcome!","Open the door..");
          break;
        default:
          LCDPRINT("Hello, Visitor!","Enter password..");
          break;
    }
}
