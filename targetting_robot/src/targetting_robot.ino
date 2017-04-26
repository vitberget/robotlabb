#include "motors.h"

#define BUTTON_PIN 9
#ifdef VERSION2
#define BUTTON_PIN 10
#endif

#define RIGHT_LINE_SENSOR A2
#define LEFT_LINE_SENSOR A3

int LEN = 5;
int leftBuf = 0;
int rightBuf = 0;
int rightLineSensorBack = 700;
int rightLineSensorCounter = 0;
int rightLineSensorCounterStart = 3500;   //1000 = 45 grader rotation (rotationstid: rightLineSensorCounterStart-rightLineSensorBack)
int whiteColor = 600;

bool shouldRun = false;
bool running = false;

bool serial = true;
bool onOff = false;

void buttonPressed() {
  cli(); // Disable interrupts
  //Serial.println("Button interupt FALLING (pressed)");
  detachInterrupt(BUTTON_PIN);
  if(shouldRun) {
    motors(0,0);
    delay(100);
    running = false;
  }
  shouldRun = !shouldRun;
  sei(); // Enable interrupts
}

int readLeft() {
  //return analogRead(A0);
  leftBuf = (leftBuf * LEN + analogRead(A1)) / (LEN+1);
  return leftBuf;
}

int readRight() {
  //return analogRead(A1);
  rightBuf = (rightBuf * LEN + analogRead(A0)) / (LEN+1);
  return rightBuf;
}

int readLineSensor(int sensor) {
  return analogRead(sensor);
}


void rotateLeft() {
  motors(-255,255);
}

void back() {
  motors(-255,-255);
}


void turn180DegreesToEscapeWhiteLine() {
  if (rightLineSensorCounter <= (rightLineSensorCounterStart-rightLineSensorBack)) {
    rotateLeft();
  } else {
    back();
  }
  //if (serial) Serial.printf("COUNTER: [%4d]", rightLineSensorCounter);
  //if (serial) Serial.println("");
  rightLineSensorCounter--;
}

void setup() {
  if(serial) Serial.begin(115200);

  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(RIGHT_LINE_SENSOR,INPUT);
  pinMode(LEFT_LINE_SENSOR,INPUT);

  motors_setup();

  pinMode(13, OUTPUT);


  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(BUTTON_PIN, buttonPressed, FALLING);
}

void loop() {
  onOff = !onOff;
  digitalWrite(13, onOff ? HIGH : LOW);

  if(!running) {
    if(shouldRun) {
      //Serial.println("Waiting to start");
      running = true;
      delay(3000);
    } else {
      //Serial.println("Waiting for button");
      delay(100);
      return;
    }
  }

  int left = readLeft();
  int right = readRight();
  int rightLineSensor = readLineSensor(RIGHT_LINE_SENSOR);
  int leftLineSensor = readLineSensor(LEFT_LINE_SENSOR);
  int diff = left - right;
  int avg = (left + right) / 2;


  //delay(500);
  //if (serial) Serial.printf("[%4d %4d %5d] ",left,right,diff);
  if (serial) Serial.printf("[%4d]", leftLineSensor);
  if (serial) Serial.printf("[%4d]", rightLineSensor);
  //if (serial) Serial.printf("[%4d %4d %5d] ",left,right,diff);


  if (rightLineSensorCounter == 0 && (rightLineSensor < whiteColor)) {
    // Found white line
    rightLineSensorCounter = rightLineSensorCounterStart;
  }

  if (rightLineSensorCounter > 0) {
    turn180DegreesToEscapeWhiteLine();
  } else {
    int ll = left/32;
    int rr = right/32;

    if (serial) Serial.print("[");
    for(int i=0; serial && i< 32; i++) {
      Serial.print(i<=ll ? "=":"-");
    }
    if (serial) Serial.print("|");
    for(int i=31; serial && i>-1; i--) {
      Serial.print(i<=rr ? "=":"-");
    }

    if(serial) Serial.print("] ");

    if(ll>rr+3) {
      if (serial) Serial.print("Left");
      motors(-255,255);
    } else if(rr>ll+3) {
      if (serial) Serial.print("Right");
      motors(255,-255);
    } else if (ll >4 && rr>4) {
      if (serial) Serial.print("Fwd");
      motors(255, 255);
    } else {
      if (serial) Serial.print("Search");
      if((millis()%8000)>4000) {
        motors(255,-255);
      } else {
        motors(-255,255);
      }
    }

    if (serial) Serial.println();
    delay(7);
  }
}
