int gndPin = 5;
int vccPin = 2;
int echoPin = 4;
int triggerPin = 3;

int buzzerPin = 7;

void setup() {
  Serial.begin(115200);
  
  pinMode(vccPin, OUTPUT);
  pinMode(gndPin, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  digitalWrite(vccPin, HIGH);
  digitalWrite(gndPin, LOW);

  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  
  unsigned long fDuration, fDistance;
  digitalWrite(triggerPin, HIGH);
  delay(10);
  digitalWrite(triggerPin, LOW);
  fDuration = pulseIn(echoPin, HIGH);
  fDistance = ((float)(340 * fDuration)) / 10000 / 2;

  if(fDistance < 5)
  {
    tone(buzzerPin, 220);
  }
  else if(fDistance < 10)
  {
    tone(buzzerPin, 220, 62);
    delay(125);
  }
  else if(fDistance < 15)
  {
    tone(buzzerPin, 220, 125);
    delay(250);
  }
  else if(fDistance < 20)
  {
    tone(buzzerPin, 220, 250);
    delay(500);
  }
  else if(fDistance < 30)
  {
    tone(buzzerPin, 220, 500);
    delay(1000);
  }

  Serial.print(fDistance);
  Serial.println("cm");
}
