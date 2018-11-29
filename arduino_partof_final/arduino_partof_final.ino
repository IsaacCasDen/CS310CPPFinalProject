#define x_dir 0
#define y_dir 1
const byte D3_RIGHT = 3;
const byte D4_UP = 4;
const byte D5_DOWN = 5;
const byte D6_LEFT = 6;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
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
  }
  if(analogRead(x_dir) <= 10)
  {
    Serial.println("L");
  }
  if(analogRead(y_dir) >= 1000)
  {
    Serial.println("U");
  }
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
//  Serial.print("x dir: ");
//  Serial.println(analogRead(x_dir));
//  Serial.print("y dir: ");
//  Serial.println(analogRead(y_dir));


  //top left is between 800 and 1000 y-dir .   "G"
  //bottom left is between 50 and 150 y-dir   "F"
  //top right is between 650 and 850 x-dir . "E"
  //bottom right is between 750 and 950 y-dir . "H"
  delay(10);
}
