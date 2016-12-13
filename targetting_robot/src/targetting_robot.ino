#define ON 1
#define OFF 0

#define LEFT_SPEED 4
#define LEFT_FORWARD 7
#define LEFT_REVERSE 8

#define RIGHT_SPEED 3
#define RIGHT_FORWARD 5
#define RIGHT_REVERSE 6

void setup() {
  Serial.begin(38400);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);

  pinMode(LEFT_SPEED, OUTPUT);
  pinMode(RIGHT_SPEED, OUTPUT);
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_REVERSE, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_REVERSE, OUTPUT);

  analogWrite(LEFT_SPEED, 200);
  analogWrite(RIGHT_SPEED, 200);
}

void loop() {
  int left = analogRead(A0);
  int right = analogRead(A1);
  int diff = left - right;
  Serial.printf("[%4d %4d %5d] ",left,right,diff);

  if(diff < -100) {
    Serial.println("Turning LEFT");
    digitalWrite(LEFT_FORWARD, OFF);
    digitalWrite(LEFT_REVERSE, ON);
    digitalWrite(RIGHT_FORWARD, ON);
    digitalWrite(RIGHT_REVERSE, OFF);
  } else if (diff > 100) {
    Serial.println("Turning RIGHT");
    digitalWrite(LEFT_FORWARD, ON);
    digitalWrite(LEFT_REVERSE, OFF);
    digitalWrite(RIGHT_FORWARD, OFF);
    digitalWrite(RIGHT_REVERSE, ON);
  } else {
    Serial.println("Turning STOP");
    digitalWrite(LEFT_FORWARD, OFF);
    digitalWrite(LEFT_REVERSE, OFF);
    digitalWrite(RIGHT_FORWARD, OFF);
    digitalWrite(RIGHT_REVERSE, OFF);
  }

  delay(133);
}
