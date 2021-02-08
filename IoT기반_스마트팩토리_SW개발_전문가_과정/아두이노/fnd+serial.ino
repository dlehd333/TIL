// Serial 통신 및 세그먼트(FND 4-Digit) 출력 예제
// 사용한 세그먼트는 공통 양극(Common Anode) 방식

#define BUF_SIZE 20

int fndPin[] = {2, 3, 4, 5, 6, 7, 8}; // 세그먼트 단자(fnd) 핀
int comPin[] = {10, 11, 12, 13}; // 세그먼트 공통단자(com) 핀
int fndNum[][7] = {
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
}; // 세그먼트에 출력할 숫자폰트 정보(0~9)

char buf[BUF_SIZE];       // 시리얼로 받은 문자열을 저장하는 버퍼
int bufIndex = 0;   // 버퍼의 사이즈를 저장하는 변수
int number = 0;     // 입력받은 숫자를 (문자열을 숫자로 변환해) 저장하는 함수

void setup() {
  Serial.begin(115200); // 시리얼 초기화, 숫자는 통신속도 설정

  for(int i = 0; i < 7; i++)    // 세그먼트 단자 핀 설정
  {
    pinMode(fndPin[i], OUTPUT);
  }
  for(int i =0; i < 4; i++)     // 세그먼트 공용 단잔 핀 설정
  {
    pinMode(comPin[i], OUTPUT);
  }
}

void loop() {

  while(Serial.available())         // 시리얼 입력버퍼에 내용이 있다?
  {
    buf[bufIndex] = Serial.read();  // 1바이트씩 문자 읽기
    bufIndex++;                     // 1바이트 읽고 버퍼 위치 변경
  }                                 // 결과적으로 버퍼의 모든 내용 읽음
  
  if(bufIndex > 0)                  // 버퍼을 읽었다면?
  {
    Serial.write(buf);              // 우선 시리얼에 출력(Echo)
    
    bool b = true;
    for(int i =0; i < bufIndex - 1; i++)  // 문자열이 숫자인지 검사 
    {
      if(!isDigit(buf[i]))                // isDigit() - 문자가 숫자인지? 참이면 true 반환
      {
        b = false;
        break;
      }
    }
    
    if(b)
      number = atoi(buf);                 // 검사결과 문자열이 숫자면 저장
  }

  showNum(0, (number % 10000)/ 1000);     // 저장된 숫자를 출력
  showNum(1, (number % 1000) / 100);      // 빠르게 한글자씩 번갈아가며 출력
  showNum(2, (number % 100) / 10);        // 사람이 보기에는 4개의 숫자가 보인다
  showNum(3, number % 10);

   for(int i =0; i < BUF_SIZE; i++)       // 작업이 끝나고 버퍼를 비워준다
    buf[i] = NULL;
   bufIndex = 0;
}

void showNum(int com, int fnd)            // 숫자를 세그먼트에 출력하는 함수
{                                         // 한글자씩 출력하므로, 출력위치와 출력숫자가 인자로 들어감
  for(int i =0; i < 4; i++)               // 입력받은 출력위치를 제외하고 꺼준다
  {
    if(com == i)
      digitalWrite(comPin[i], HIGH);
    else
      digitalWrite(comPin[i], LOW); 
  }

  for(int i =0; i < 7; i++)               // 해당 자리의 숫자를 출력숫자로 변경해준다
    digitalWrite(fndPin[i], fndNum[fnd][i]);

  delay(2);                               // 선명하게 찍히기 위해 살짝 딜레이를 준다
}
