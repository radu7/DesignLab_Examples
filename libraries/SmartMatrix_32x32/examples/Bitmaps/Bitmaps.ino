/*
 * This demo shows how to display bitmaps that are exported from GIMP and
 * compiled into the sketch and stored in the Teensy's Flash memory
 * See more details here:
 * http://docs.pixelmatix.com/SmartMatrix/library.html#drawing-raw-bitmaps
 */
 
/*
    Papilio Notes:
    
    Hardware: Use a RGB LED Panel Wing connected to row D on the Papilio DUO and row C on the Papilio Pro.
    http://store.gadgetfactory.net/rgb-led-panel-wing/?page_context=category&faceted_search=0
    
*/

#define circuit RGB_Matrix 

#include <SmartMatrix_32x32.h>

#include "gimpbitmap.h"

// pixelmatix.c is a bitmap exported from GIMP without modification
#include "pixelmatix.c"

// colorwheel.c has been modified to use the gimp32x32bitmap struct
#include "colorwheel.c"

// chrome16 is a 16x16 pixel bitmap, exported from GIMP without modification
#include "chrome16.c"

const rgb24 COLOR_BLACK = rgb24(0, 0, 0 );

SmartMatrix matrix;

int led = 13;

void drawBitmap(int16_t x, int16_t y, const gimp32x32bitmap* bitmap) {
  for(unsigned int i=0; i < bitmap->height; i++) {
    for(unsigned int j=0; j < bitmap->width; j++) {
      rgb24 pixel = rgb24( bitmap->pixel_data[(i*bitmap->width + j)*3 + 0],
                      bitmap->pixel_data[(i*bitmap->width + j)*3 + 1],
                      bitmap->pixel_data[(i*bitmap->width + j)*3 + 2] );

      matrix.drawPixel(x + j, y + i, pixel);
    }
  }
}

void setup() {
  matrix.begin();
  matrix.setBrightness(128);

  pinMode(led, OUTPUT);
}

void loop() {
  matrix.fillScreen(COLOR_BLACK);
  // to use drawBitmap, must cast the pointer to pixelmatixlogo as (const gimp32x32bitmap*)
  drawBitmap(0,0,(const gimp32x32bitmap*)&pixelmatixlogo);
  matrix.swapBuffers();

  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);

  matrix.fillScreen(COLOR_BLACK);
  // can pass &colorwheel in directly as the bitmap source is already gimp32x32bitmap
  drawBitmap(0,0,&colorwheel);
  matrix.swapBuffers();

  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);


  matrix.fillScreen(COLOR_BLACK);
  // draw this smaller bitmap centered
  int x = (MATRIX_WIDTH / 2) - (chrome16.width/2);
  int y = (MATRIX_HEIGHT / 2) - (chrome16.height/2);
  drawBitmap(x, y, (const gimp32x32bitmap*)&chrome16);
  matrix.swapBuffers();

  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
}
