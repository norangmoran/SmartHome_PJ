#include <Servo.h>
#include <Wire.h>
char LOCK='N';
Servo DoorLock; //서보모터 제어용 객체생성

void setup(){
  Wire.begin();
  
  Serial.begin(9600);
  DoorLock.attach(13); //서보모터 Data핀
}

void loop(){
  while(Serial.available()){
  	LockSys(Serial.read());
  }
}
void CallMaster(){ //3회 접속실패시
  LCDPRINT("A Number of Failures","Close for 30 sec..");
  Serial.println("Access fail"); //라즈베리에서 사진촬영,주인에게 메세지전송!
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

void RoomMode(int RM){ //조명모드 선택
  switch(RM) {
    case 1://아침 기상모드
      ONOFFCont(1);
      RGB1(242,0,0);
      //RGB(242,230,150)주백색-활동적인 에너지를 주는 색. 주방, 몸 움직이는 일.
      break;
    case 2://일상 생활모드
      ONOFFCont(0);
      RGB1(235,255,255);
      //RGB(235,255,255)백색-상쾌함. 긴장감. 책읽기, 사무공간.
      break;
    case 3://오후 휴식모드
      ONOFFCont(1);
      RGB1(223,140,50);
      //RGB(223,140,50)전구색-백열전구와 비슷. 안정감을 주는 휴식공간.
      break;
    case 4: //저녁 취침모드
      ONOFFCont(2);
      break;
    default: //외출 소등
      ONOFFCont(6);
      break;
  }
}

void DoorLock(char LOCK){ //도어락 잠금열림
  switch(LOCK){
    case 'Y':
      myservo.write(0); //angle 0도. 열림
      break;
    default:
      myservo.write(90); //angle 90도. 닫힘
      break;
  }
}
void ONOFFCont(int cont) { //조명 OnOff컨트롤. 시프트레지스터 제어.
  digitalWrite(latch,LOW);
  shiftOut(data,clock,MSBFIRST,cont);
  digitalWrite(latch,HIGH);
}
void RGB1(int R,int G,int B){ //거실창가 조명
  analogWrite(red1,R);
  analogWrite(green1,G);
  analogWrite(blue1,B);
}
void RGB2(int R,int G,int B){ //거실내부 조명
 analogWrite(red2,R);
 analogWrite(green2,G);
 analogWrite(blue2,B);
}
