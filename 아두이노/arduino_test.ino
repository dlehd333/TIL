#include <Stepper.h>  // 스텝모터 라이브러리
#include <Wire.h>
#include <LiquidCrystal_I2C.h>  // LCD 라이브러리
const int stepRotation = 2048;  // 스텝모터 한바퀴 크기

int pinX = A11;   // 조이스틱 x
int pinY = A12;   // 조이스틱 y
int pinSw = A13;  // 조이스틱 누르기
int led = 13;     // LED
int fndPin[7] = {5, 6, 7, 8, 9, 10, 11};  // fnd
int comPin[] = {14,15,16,17}; // fnd common
int fndNum[][7] = { // fnd로 출력할 숫자
  {0,0,0,0,0,0,1},
  {1,0,0,1,1,1,1},
  {0,0,1,0,0,1,0},
  {0,0,0,0,1,1,0},
  {1,0,0,1,1,0,0},
  {0,1,0,0,1,0,0},
  {0,1,0,0,0,0,0},
  {0,0,0,1,1,0,1},
  {0,0,0,0,0,0,0},
  {0,0,0,0,1,0,0}
};
int stMotor[4] = {22, 23, 24, 25}; // 스텝모터 전자석

int buzzer = 52;  // 부저
int fData[] = {130, 147, 165, 174, 196, 220, 247, 261, 293};  // 부저로 출력할 주파수(계이름)

enum {C = 0, D, E, F, G, A, B, C2, D2, N};  // 음악 출력을 위한 계이름 설정

struct Music{ // 음악 출력을 위한 음악 구조체.
  int key;    // 음계
  float note; // 음표
};

struct Music edelweiss[] = {    // 음계와 음표 정보로 저장한 음악 배열
  {E,2}, {G,1}, {D2,3}, {C2,2}, {G,1}, {F,3},
  {E,2}, {E,1}, {E,1}, {F,1}, {G,1}, {A,3}, {G,3},
  {E,2}, {G,1}, {D2,3}, {C2,2}, {G,1}, {F,3},
  {E,2}, {G,1}, {G,1}, {A,1}, {B,1}, {C2,3}, {C2,3}};

int num = 0;    // 모듈의 카운트에 사용할 변수
int buzNum = 0; // 부저 음악 진행 카운트

Stepper myStepper(stepRotation, stMotor[3],stMotor[1],stMotor[2],stMotor[0]);
LiquidCrystal_I2C lcd(0x27, 16, 2);   // 스텝퍼, LCD 객체 초기화

void setup() {
  Serial.begin(9600);       // 시리얼 출력 설정
  pinMode(pinX, INPUT);     // 조이스틱 pinX
  pinMode(pinY, INPUT);     // 조이스틱 pinY
  pinMode(pinSw, INPUT_PULLUP); // 조이스틱 누르기
  
  pinMode(led, OUTPUT);   // LED
  
  for(int i = 0; i < 7; i++)    // fnd
    pinMode(fndPin[i], OUTPUT);
  for(int i = 0; i< 4;i++)      // fnd common
    pinMode(comPin[i], OUTPUT);

  pinMode(buzzer, OUTPUT);    // 부저

  myStepper.setSpeed(15);     // 스텝모터

  lcd.init();         // lcd
  lcd.backlight();    // lcd 불 켜기
  lcd.clear();        // lcd 지우기
  
  Serial.println(" ++++ Menu ++++");    // 시리얼 출력, 어떤 기능이 있는지 안내
  Serial.println("1. Left - LED");
  Serial.println("2. Right - FND 4-Digit");
  Serial.println("3. Up - Buzzer");
  Serial.println("4. Down - Step Motor");
  Serial.println("5. push S/W - LCD");
}

void loop() {
  // 조이스틱의 x,y 아날로그 값의 사용 범위를 조정
  int X = map(analogRead(pinX), 0, 1023, -5, 5);
  int Y = map(analogRead(pinY), 0, 1023, -5, 5);
  // left : x = -5 // right : x = 5 // up : y = -5 // down : y = 5

  if(X == -5)   // 왼쪽으로
  {
    digitalWrite(led, HIGH);  // LED를 0.1초마다 꺼졌다 켜졌다 하게 한다
    delay(100);
    digitalWrite(led, LOW);
    delay(100);
  }
  else if(X == 5)   // 오른쪽으로
  {
    showNum(0, (num % 10000) / 1000); // 함수를 이용해 한자리씩 빠르게 출력하여
    showNum(1, (num % 1000) / 100);   // 동적 디스플레이로 4개의 숫자가 보이게 한다
    showNum(2, (num % 100) / 10);
    showNum(3, num % 10);
    num++;  // 카운트 증가
  }
  else if(Y == -5)  // 위
  {
    sound(edelweiss[buzNum].key, edelweiss[buzNum].note); // 함수를 이용해 음악 출력
    buzNum++;   // 진행도를 위한 카운트
    if(buzNum >= sizeof(edelweiss) / sizeof(struct Music)) buzNum = 0;  // 음악이 끝나면 처음으로
  }
  else if(Y == 5)
  {
    myStepper.step(10); // 모터를 정방향으로 전진
  }
  else if(!digitalRead(pinSw))
  {
    lcd.backlight();      // lcd의 백라이트를 켠다
    lcd.setCursor(0,0);   // 커서를 윗줄 처음으로
    lcd.print("elapsed time");  // 문자 출력
    lcd.setCursor(0,1);   // 커서를 아랫줄 처음으로
    lcd.print(num);       // 카운트된 숫자 출력
    lcd.print("sec");     // 문자 출력
    delay(1000);           // 확인을 위한 딜레이(1초마다 바뀌게)
    num++;                 // 카운트
  }
  else
  {
    digitalWrite(led,LOW);          // 미작업시 LED OFF

    for(int i =0; i < 4; i++)       // 미작업시 FND COMMON OFF
      digitalWrite(comPin[i], LOW);
    
    num = 0;                        // 미작업시 카운트 0으로

    buzNum = 0;                     // 미작업시 음악 진행도 카운트 0으로
    noTone(buzzer);                 // 미작업시 부저 종료

    lcd.clear();                    // 미작업시 LCD 지우기
    lcd.noBacklight();              // 미작업시 LCD 백라이트 끄기
  }
}

void showNum(int com, int fnd)      // FND 숫자 출력 함수
{
  for(int i =0; i < 4; i++)   // 출력할 COM을 제외하고 끈다
  {
    if(com == i)
      digitalWrite(comPin[i], HIGH);
    else
      digitalWrite(comPin[i], LOW); 
  }

  for(int i =0; i < 7; i++)   // 지정된 숫자를 출력한다
    digitalWrite(fndPin[i], fndNum[fnd][i]);

  delay(5);   // 잔상 조절을 위한 딜레이
}

void sound(int key, float note) // 부저로 음을 출력하는 함수
{
  if(key != N)                  // 쉼표가 아니라면
    tone(buzzer, fData[key]);   // 주파수에 맞게 부저를 울린다
  delay(note * 300);            // 지정된 음표(박자)만큼 딜레이
  noTone(buzzer);               // 부저를 끈다
}
