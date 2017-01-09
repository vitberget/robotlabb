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

  motors(0,0);
}

void motors(int leftSpeed, int rightSpeed) {
  analogWrite(LEFT_SPEED, min(255, abs(leftSpeed)));
  analogWrite(RIGHT_SPEED, min(255, abs(rightSpeed)));

  if(leftSpeed==0) {
    digitalWrite(LEFT_FORWARD, OFF);
    digitalWrite(LEFT_REVERSE, OFF);
  } else if(leftSpeed<0) {
    digitalWrite(LEFT_FORWARD, OFF);
    digitalWrite(LEFT_REVERSE, ON);
  } else {
    digitalWrite(LEFT_FORWARD, ON);
    digitalWrite(LEFT_REVERSE, OFF);
  }

  if(rightSpeed==0) {
    digitalWrite(RIGHT_FORWARD, OFF);
    digitalWrite(RIGHT_REVERSE, OFF);
  } else if(rightSpeed<0) {
    digitalWrite(RIGHT_FORWARD, OFF);
    digitalWrite(RIGHT_REVERSE, ON);
  } else {
    digitalWrite(RIGHT_FORWARD, ON);
    digitalWrite(RIGHT_REVERSE, OFF);
  }
}

void loop() {
  Serial.printf("HEJ");
  int left = readLeft();
  int right = readRight();
  int diff = left - right;
  int avg = (left + right) / 2;

  Serial.printf("[%4d %4d %5d] ",left,right,diff);

  if (avg>600) {
    Serial.println("KILL!!!");
    motors(200,200);
  } else if(diff < -25) {
    Serial.println("Turning LEFT");
    motors(-200,200);
  } else if (diff > 25) {
    Serial.println("Turning RIGHT");
    motors(200,-200);
  } else if (left>400 && right>400) {
    Serial.println("ATTACK!!!");
    motors(200,200);
  } else {
    Serial.println("Turning STOP");
    motors(0,0);
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
