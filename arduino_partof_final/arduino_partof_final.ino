#define x_dir 0
#define y_dir 1
const byte D3_RIGHT = 3;
const byte D4_UP = 4;
const byte D5_DOWN = 5;
const byte D6_LEFT = 6;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(10);
  pinMode(D3_RIGHT, INPUT);
  digitalWrite(D3_RIGHT, HIGH);
  pinMode(D4_UP, INPUT);
  digitalWrite(D4_UP, HIGH);
  pinMode(D5_DOWN, INPUT);
  digitalWrite(D5_DOWN, HIGH);
  pinMode(D6_LEFT, INPUT);
  digitalWrite(D6_LEFT, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(analogRead(x_dir) >= 1000)
  {
    Serial.println("R");
  } else
  if(analogRead(x_dir) <= 10)
  {
    Serial.println("L");
  }
  
  if(analogRead(y_dir) >= 1000)
  {
    Serial.println("U");
  } else
  if(analogRead(y_dir) <= 10)
  {
    Serial.println("D");
  }
  
  if(digitalRead(D3_RIGHT) == LOW)
  {
    Serial.println("A");
  }
  if(digitalRead(D4_UP) == LOW)
  {
    Serial.println("X");
  }
  if(digitalRead(D5_DOWN) == LOW)
  {
    Serial.println("B");
  }
  if(digitalRead(D6_LEFT) == LOW)
  {
    Serial.println("Y");
  }
  delay(250);
}
