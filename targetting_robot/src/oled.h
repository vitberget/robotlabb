#include "Arduino.h"
#include <SPI.h>
#include <TeensyView.h>

void oled_begin();

//void oled_show(String text);
//void oled_show(String text, int left1, int right1);
//void oled_show(String text, int left1, int right1, int left2, int right2);
void oled_show(String text, int left1=0, int right1=0, int left2=0, int right2=0, int left3=0, int right3=0);
