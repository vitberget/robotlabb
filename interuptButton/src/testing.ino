#include <avr/io.h>
#include <avr/interrupt.h>

#define pin 7

void setup() {
  Serial.begin(38400);
  pinMode(pin, INPUT_PULLUP);
  attachInterrupt(pin, isrFalling, FALLING);
}

void isrFalling()
{
  cli();
  Serial.println("Button interupt FALLING (pressed)");
  attachInterrupt(pin, isrRising, RISING);
  sei();
}


void isrRising()
{
  cli();
  Serial.println("Button interupt RISING (released)");
  attachInterrupt(pin, isrFalling, FALLING);
  sei();
}

void loop()
{
  if (digitalRead(pin) == HIGH) {
    Serial.println("Button is not pressed...");
  } else {
    Serial.println("Button pressed!!!");
  }
  delay(250);
}
