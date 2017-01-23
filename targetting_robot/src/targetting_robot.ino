#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


#define ON 1
#define OFF 0

#define LEFT_SPEED 4
#define LEFT_FORWARD 7
#define LEFT_REVERSE 8

#define RIGHT_SPEED 3
#define RIGHT_FORWARD 5
#define RIGHT_REVERSE 6

#define BUTTON_PIN 9
#define NEOPIXEL_PIN 11
#define NEOPIXEL_LEDS 1

int LEN = 10;
int leftBuf = 0;
int rightBuf = 0;

bool shouldRun = false;
bool running = false;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NEOPIXEL_LEDS, NEOPIXEL_PIN, NEO_RGB + NEO_KHZ800);

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

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(BUTTON_PIN, buttonPressed, FALLING);

  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(0,150,0));
  pixels.show();

}

void buttonPressed() {
  cli(); // Disable interrupts
  Serial.println("Button interupt FALLING (pressed)");
  if(shouldRun) {
    motors(0,0);
    delay(10);
    shouldRun = false;
    running = false;
    pixels.setPixelColor(0, pixels.Color(0,150,0));
    pixels.show();
  } else {
      shouldRun = true;
  }

  sei(); // Enable interrupts

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
  if(!running) {
    if(shouldRun) {
      Serial.println("Waiting to start");
      running = true;
      pixels.setPixelColor(0, pixels.Color(150,150,0));
      pixels.show();
      delay(3000);
      pixels.setPixelColor(0, pixels.Color(150,0,0));
      pixels.show();
    } else {
      Serial.println("Waiting for button");
      delay(50);
      return;
    }
  }

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
