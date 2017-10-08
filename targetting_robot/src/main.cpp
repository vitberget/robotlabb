#include "Arduino.h"
#include "motors.h"


#define BUTTON_PIN 10
#define LED_PIN 13

//#define RIGHT_LINE_SENSOR A2
//#define LEFT_LINE_SENSOR A3

#define LEFT_DISTANCE_SENSOR A1
#define RIGHT_DISTANCE_SENSOR A0


const int ROLLING_AVERAGE_WIDTH = 5;

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
  shouldRun = true;
  //sei(); // Enable interrupts
}

typedef struct RollingAverage {
  int values[ROLLING_AVERAGE_WIDTH];
  int head = 0;
} RollingAverage;

void setup() {
  if(serial) Serial.begin(115200);

  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  //pinMode(RIGHT_LINE_SENSOR,INPUT);
  //pinMode(LEFT_LINE_SENSOR,INPUT);

  motors_setup();

  pinMode(LED_PIN, OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(BUTTON_PIN, buttonPressed, FALLING);
}

int average(RollingAverage* ra, int value) {
  if (ra->head >= ROLLING_AVERAGE_WIDTH)
    ra->head = 0;
  ra->values[ra->head++] = value;
  int sum = 0;
  for (int i = 0; i < ROLLING_AVERAGE_WIDTH; i++) {
    sum = sum + ra->values[i];
  }
  int average = sum / ROLLING_AVERAGE_WIDTH;
  return average;
}

RollingAverage leftAverage, rightAverage;


void loop() {
  onOff = !onOff;
  digitalWrite(LED_PIN, onOff ? HIGH : LOW);

  if(!running) {
    if(shouldRun) {
      //Serial.println("Waiting to start");
      running = true;
      delay(1000);
    } else {
      //Serial.println("Waiting for button");
      delay(200);
      return;
    }
  }


  int left = average(&leftAverage, analogRead(LEFT_DISTANCE_SENSOR));
  int right = average(&rightAverage, analogRead(RIGHT_DISTANCE_SENSOR));

  {
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
