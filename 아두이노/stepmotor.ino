#include <Stepper.h>  // 라이브러리 추가
#define rot A0        // 가변저항 output값

const int stepRotation = 2048; // 한바퀴 크기, 반바퀴는 1024
Stepper myStepper(stepRotation, 11, 9, 10, 8);  // 스텝퍼 객체 생성
// 순서대로 IN4, IN2, IN3, IN1

void setup() {
  myStepper.setSpeed(10); // 모터의 속도 설정
  Serial.begin(9600);
}

void loop() {
  int value = map(analogRead(rot), 0, 1023, 0, 2017); // 가변저항의 값을 받아와 스텝모터의 스텝에 맞게 바꿔준다
  // map -> 해당 value에 들어오는 값을 원래 범위에서 새로운 범위에 맞게 수정해준다
  Serial.println(value);
  myStepper.step(value); // 정방향 1바퀴
  delay(100);
  myStepper.step(-value);  // 역방향 1바퀴
  delay(100);
}