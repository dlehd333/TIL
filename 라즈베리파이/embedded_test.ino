int pinX = A2;
int pinY = A3;
int pinSw = A4;

void setup() {  
  Serial.begin(9600); // pc 연결
  Serial1.begin(9600);  // 라즈베리파이 연결
  pinMode(pinX, INPUT); // 조이스틱x
  pinMode(pinY, INPUT); // 조이스틱y
}

void loop() {
  int X = analogRead(pinX); // 조이스틱x adc값
  int Y = analogRead(pinY); // 조이스틱y adc값
  
  Serial.print("X: ");  // 시리얼에 값 출력
  Serial.print(X);
  Serial.print("\tY: ");
  Serial.println(Y);
  
  Serial1.print("x"); // 라즈베리파이에 값 전달
  Serial1.println(X);
  Serial1.print("y");
  Serial1.println(Y);

  delay(500);
}
