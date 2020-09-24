#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS1302.h>               // 라이브러리 추가

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD 객체 추가(주소, 가로길이, 세로길이)
DS1302 rtc(10, 9, 8); // RTC 객체 추가(RST, DAT, CLK)

void setup() {
  Serial.begin(9600); // 시리얼 초기화, 이후 시리얼 관련 함수는 주석 생략

  rtc.setDOW(THURSDAY); // 요일 설정
  rtc.setTime(10, 27, 50); // 시, 분, 초 시간 설정
  rtc.setDate(24, 9, 2020); // 일, 월, 년 날짜 설정

  lcd.init();       // LCD 초기화, 이후 LCD 관련 함수는 주석 생략
  lcd.backlight();
  lcd.clear();
}

// RTC에서 값을 받아와, 시간이 잘 흘러가고 있는지 확인한다.
// 출력 부분은 주석 생략
void loop() {
  Serial.print(rtc.getDOWStr());    // 요일 출력 - Thursday
  Serial.print(" ");
  Serial.print(rtc.getDateStr());   // 날짜 출력 - 24.9.2020
  Serial.print(" ");
  Serial.println(rtc.getTimeStr()); // 시간 출력 - 10:27:50

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(rtc.getDateStr());
  lcd.setCursor(11,0);
  lcd.print(rtc.getDOWStr());
  lcd.setCursor(0,1);
  lcd.print(rtc.getTimeStr());
  
  delay(1000);
}
