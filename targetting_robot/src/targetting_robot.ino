#define ON 1
#define OFF 0

#define LEFT_SPEED 4
#define LEFT_FORWARD 7
#define LEFT_REVERSE 8

#define RIGHT_SPEED 3
#define RIGHT_FORWARD 5
#define RIGHT_REVERSE 6

int LEN = 10;
int leftBuf = 0;
int rightBuf = 0;

void setup() {
  Serial.begin(38400);

  pinMode(A0,INPUT);
  pinMode(A1,INPUT);

  pinMode(RIGHT_SPEED, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_REVERSE, OUTPUT);

  pinMode(LEFT_SPEED, OUTPUT);
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_REVERSE, OUTPUT);

}

void loop() {
  Serial.printf("HEJ");
  int left = readLeft();
  int right = readRight();
  int diff = left - right;
  Serial.printf("[%4d %4d %5d] ",left,right,diff);

  if (left>600 && right>600) {
    Serial.println("KILL!!!");

    analogWrite(LEFT_SPEED, 200);
    analogWrite(RIGHT_SPEED, 200);
    digitalWrite(LEFT_FORWARD, ON);
    digitalWrite(LEFT_REVERSE, OFF);
    digitalWrite(RIGHT_FORWARD, ON);
    digitalWrite(RIGHT_REVERSE, OFF);

  } else   if(diff < -25) {
    Serial.println("Turning LEFT");

    analogWrite(LEFT_SPEED, 200);
    analogWrite(RIGHT_SPEED, 200);
    digitalWrite(LEFT_FORWARD, OFF);
    digitalWrite(LEFT_REVERSE, ON);
    digitalWrite(RIGHT_FORWARD, ON);
    digitalWrite(RIGHT_REVERSE, OFF);
  } else if (diff > 25) {
    Serial.println("Turning RIGHT");

    analogWrite(LEFT_SPEED, 200);
    analogWrite(RIGHT_SPEED, 200);
    digitalWrite(LEFT_FORWARD, ON);
    digitalWrite(LEFT_REVERSE, OFF);
    digitalWrite(RIGHT_FORWARD, OFF);
    digitalWrite(RIGHT_REVERSE, ON);
  } else if (left>400 && right>400) {
    Serial.println("ATTACK!!!");

    analogWrite(LEFT_SPEED, 200);
    analogWrite(RIGHT_SPEED, 200);
    digitalWrite(LEFT_FORWARD, ON);
    digitalWrite(LEFT_REVERSE, OFF);
    digitalWrite(RIGHT_FORWARD, ON);
    digitalWrite(RIGHT_REVERSE, OFF);

  } else {
    Serial.println("Turning STOP");
    digitalWrite(LEFT_FORWARD, OFF);
    digitalWrite(LEFT_REVERSE, OFF);
    digitalWrite(RIGHT_FORWARD, OFF);
    digitalWrite(RIGHT_REVERSE, OFF);
  }

  delay(33);
}

int readLeft() {
  leftBuf = (leftBuf * LEN + analogRead(A0)) / (LEN+1);
  return leftBuf;
}

int readRight() {
  rightBuf = (rightBuf * LEN + analogRead(A1)) / (LEN+1);
  return rightBuf;
}
