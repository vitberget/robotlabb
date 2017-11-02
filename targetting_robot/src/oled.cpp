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

TeensyView oled(PIN_RESET, PIN_DC, PIN_CS, PIN_SCK, PIN_MOSI);

void oled_begin() {

  oled.begin();    // Initialize the OLED
  oled.clear(ALL); // Clear the display's internal memory
  //oled.display();  // Display what's in the buffer (splashscreen)
  //delay(1000);     // Delay 1000 ms
  oled.clear(PAGE); // Clear the buffer.

  oled.setFontType(0);  // Set font to type 0
  oled.setCursor(0, 0); // Set cursor to top-left

  oled.printf("Push the button");
  oled.display();
}

void oled_show(String text, int distance_left, int distance_right) {
  oled.clear(PAGE);
  oled.setFontType(0);  // Set font to type 0
  oled.setCursor(0, 0); // Set cursor to top-left

  oled.print(text);




  oled.display();
}
