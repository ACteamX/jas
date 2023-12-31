/*
  Pixie ANIMATION Example
  -----------------------
  
  By quickly writing to the displays in 5-column icon format,
  it is possible to run animations!
  
  Animations frames can be created at:
  https://connornishijima.github.io/Pixie/extras/icon_generator.html
*/

#include "Pixie.h"
#define NUM_PIXIES  6                     // PCBs, not matrices
#define CLK_PIN     4                     // Any digital pin
#define DATA_PIN    5                     // Any digital pin
Pixie pix(NUM_PIXIES, CLK_PIN, DATA_PIN); // Set up display buffer

uint8_t animation[24][5] = { // 24 arrays of 5 uint8_t's (Icons)
  {0x01,0x00,0x00,0x00,0x00},
  {0x01,0x01,0x00,0x00,0x00},
  {0x01,0x01,0x01,0x00,0x00},
  {0x01,0x01,0x01,0x01,0x00},
  {0x01,0x01,0x01,0x01,0x01},
  {0x00,0x01,0x01,0x01,0x03},
  {0x00,0x00,0x01,0x01,0x07},
  {0x00,0x00,0x00,0x01,0x0F},
  {0x00,0x00,0x00,0x00,0x1F},
  {0x00,0x00,0x00,0x00,0x3E},
  {0x00,0x00,0x00,0x00,0x7C},
  {0x00,0x00,0x00,0x40,0x78},
  {0x00,0x00,0x40,0x40,0x70},
  {0x00,0x40,0x40,0x40,0x60},
  {0x40,0x40,0x40,0x40,0x40},
  {0x60,0x40,0x40,0x40,0x00},
  {0x70,0x40,0x40,0x00,0x00},
  {0x78,0x40,0x00,0x00,0x00},
  {0x7C,0x00,0x00,0x00,0x00},
  {0x3E,0x00,0x00,0x00,0x00},
  {0x1F,0x00,0x00,0x00,0x00},
  {0x0F,0x00,0x00,0x00,0x00},
  {0x07,0x00,0x00,0x00,0x00},
  {0x03,0x00,0x00,0x00,0x00}
};

void setup() {
  pix.begin(); // Init display drivers
}

void loop() {
  // The 24 cusotm icons in the array above are stored as column data,
  // and are written to the left-most display in the chain.
  for(uint8_t i = 0; i < 24; i++){
    pix.write(animation[i], 0);
    pix.show();
  }
}