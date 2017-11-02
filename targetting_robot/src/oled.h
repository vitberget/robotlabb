#include "Arduino.h"
#include <SPI.h>
#include <TeensyView.h>

void oled_begin();
void oled_show(String text, int distance_left, int distance_right);
