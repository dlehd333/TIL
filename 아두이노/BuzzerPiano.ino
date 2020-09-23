int buzzerPin = 7; // gcc핀, gnd는 gnd에 연결
int fData[] = {130, 147, 165, 174, 196, 220, 247, 261, 293};

enum {C = 0, D, E, F, G, A, B, C2, D2, N};

struct Music{
  int key;
  float note;
};

struct Music edelweiss[] = {
  {E,2}, {G,1}, {D2,3}, {C2,2}, {G,1}, {F,3},
  {E,2}, {E,1}, {E,1}, {F,1}, {G,1}, {A,3}, {G,3},
  {E,2}, {G,1}, {D2,3}, {C2,2}, {G,1}, {F,3},
  {E,2}, {G,1}, {G,1}, {A,1}, {B,1}, {C2,3}, {C2,3},
  {D2,0.5}, {N,1}, {G,0.5}, {G,1}, {B,1}, {A,1}, {G,1}, {E,2}, {G,1}, {C2,3},
  {A,2}, {C2,1}, {D2,2}, {C2,1}, {B,3}, {G,3},
  {E,2}, {G,1}, {D2,3}, {C2,2}, {G,1}, {F,3},
  {E,2}, {G,1}, {G,1}, {A,1}, {B,1}, {C2,3}, {C2,3}
};

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  for(int i = 0; i < sizeof(edelweiss) / sizeof(struct Music); i++)
    sound(edelweiss[i].key, edelweiss[i].note);
}

void sound(int key, float note)
{
  if(key != N)
    tone(buzzerPin, fData[key]);
  delay(note * 500);
  noTone(buzzerPin);
}
