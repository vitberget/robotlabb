#include "Arduino.h"
#include <SPI.h>
#include <TeensyView.h>

// Call this one in begin() { ... }
void oled_begin();

// Use 1-64 for left and right values
// No rangecheck
//
// oled_show("Example1");
// oled_show("Example2", 15, 43);
// oled_show("Example2", 15, 43, 64, 12, 64, 23);
void oled_show(String text, int left1=0, int right1=0, int left2=0, int right2=0, int left3=0, int right3=0);
