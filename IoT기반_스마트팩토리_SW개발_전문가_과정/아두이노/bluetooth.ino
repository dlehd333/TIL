#include <SoftwareSerial.h>         // 통신을 위한 SoftwareSerial 라이브러리

#define BT_RXD 11
#define BT_TXD 10                   // 통신을 위한 블루투스 RX, TX 핀
#define LED 7                       // 통신 테스트를 위한 LED 핀

#define MAX_BUF 30

SoftwareSerial Bluetooth(BT_TXD, BT_RXD); // 소프트웨어시리얼 객체 생성

char res[MAX_BUF];
int res_sz;

void setup() {
  pinMode(LED, OUTPUT);             // 테스트용 LED
  
  Serial.begin(9600);               // 기본 시리얼
  Serial.println(" ");
  Serial.println("AT Mode.");
  Bluetooth.begin(9600);            // 블루투스를 연결한 소프트웨어시리얼
}

void loop() {
  res_sz = 0;                       // 버퍼 초기화
  for(int i = 0; i < MAX_BUF; i++)  //
    res[i] = NULL;                  //
  
  while(Bluetooth.available() > 0)  // 블루투스 입력 확인
  {
    res[res_sz] = Bluetooth.read();
    res_sz = res_sz + 1;
  }
  if(res_sz > 0)
  {
    Serial.print("[Bluetooth] : ");
    Serial.print(res);
    Serial.print(" - size : ");
    Serial.println(res_sz);
  }

  if(strcmp(res, "1") == 0)         // 블루투스에서 '1'이 입력되면 LED를 켠다
    digitalWrite(LED, HIGH);
  else if(strcmp(res, "0") == 0)    // '0'이 입력되면 LED를 끈다
    digitalWrite(LED, LOW);

  res_sz = 0;                       // 버퍼 초기화
  for(int i = 0; i < MAX_BUF; i++)  //
    res[i] = NULL;                  //

  while(Serial.available() > 0)     // 테스트를 위한 시리얼 입력 확인
  {                                 // 시리얼과 소프트웨어시리얼의 사용법이 거의 같다
    res[res_sz] = Serial.read();
    res_sz = res_sz + 1;
  }
  if(res_sz > 0)
  {
    Bluetooth.print(res);
    
    Serial.print("[Serial] : ");
    Serial.print(res);
    Serial.print(" - size : ");
    Serial.println(res_sz);
  }

  delay(500);                      // 버퍼를 받을 시간을 위해 약간의 딜레이를 걸어준다
}
