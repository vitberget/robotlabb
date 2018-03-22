#include "oled.h"

//Standard
//#define PIN_RESET 15
//#define PIN_DC    5
//#define PIN_CS    10
#define PIN_SCK   13
#define PIN_MOSI  11

//Alternate (Audio)
#define PIN_RESET 2
#define PIN_DC    21
#define PIN_CS    20
//#define PIN_SCK   14
//#define PIN_MOSI  7

const int LINE_Y_1=15;
const int LINE_Y_2=23;
const int LINE_Y_3=31;

TeensyView oled(PIN_RESET, PIN_DC, PIN_CS, PIN_SCK, PIN_MOSI);

void oled_begin() {

  oled.begin();    // Initialize the OLED
  oled.clear(ALL); // Clear the display's internal memory
  //oled.display();  // Display what's in the buffer (splashscreen)
  //delay(1000);     // Delay 1000 ms
  oled.clear(PAGE); // Clear the buffer.

  oled.setFontType(0);  // Set font to type 0
  oled.setCursor(0, 0); // Set cursor to top-left

  oled.printf("Push the button??");
  oled.display();
}

void oled_show(String text, int left1, int right1,
                            int left2, int right2,
                            int left3, int right3) {
  oled.clear(PAGE);
  oled.setFontType(0);  // Set font to type 0
  oled.setCursor(0, 0); // Set cursor to top-left

  oled.print(text);

  if(left1>0)  oled.line(0, LINE_Y_1, left1, LINE_Y_1);
  if(right1>0) oled.line(128-right1, LINE_Y_1, 128, LINE_Y_1);

  if(left2>0)  oled.line(0, LINE_Y_2, left2, LINE_Y_2);
  if(right2>0) oled.line(128-right2, LINE_Y_2, 128, LINE_Y_2);

  if(left3>0)  oled.line(0, LINE_Y_3, left3, LINE_Y_3);
  if(right3>0) oled.line(128-right3, LINE_Y_3, 128, LINE_Y_3);

  oled.display();
}
