/*
 * Animated GIFs Display Code for SmartMatrix and 32x32 RGB LED Panels
 *
 * Uses SmartMatrix Library for Teensy 3.1 written by Louis Beaudoin at pixelmatix.com
 *
 * Written by: Craig A. Lindley
 *
 * Copyright (c) 2014 Craig A. Lindley
 * Refactoring by Louis Beaudoin (Pixelmatix)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

 /*
  * This example displays 32x32 GIF animations loaded from a SD Card connected to the Teensy 3.1
  * The GIFs can be up to 32 pixels in width and height.
  * This code has been tested with 32x32 pixel and 16x16 pixel GIFs, but is optimized for 32x32 pixel GIFs.
  *
  * Wiring is on the default Teensy 3.1 SPI pins, and chip select can be on any GPIO,
  * set by defining SD_CS in the code below
  * Function     | Pin
  * DOUT         |  11
  * DIN          |  12
  * CLK          |  13
  * CS (default) |  15
  *
  * This code first looks for .gif files in the /gifs/ directory
  * (customize below with the GIF_DIRECTORY definition) then plays random GIFs in the directory,
  * looping each GIF for DISPLAY_TIME_SECONDS
  *
  * This example is meant to give you an idea of how to add GIF playback to your own sketch.
  * For a project that adds GIF playback with other features, take a look at
  * Light Appliance and Aurora:
  * https://github.com/CraigLindley/LightAppliance
  * https://github.com/pixelmatix/aurora
  *
  * If you find any GIFs that won't play properly, please attach them to a new
  * Issue post in the GitHub repo here:
  * https://github.com/pixelmatix/AnimatedGIFs/issues
  *
  */
  
/*
    Papilio Notes:
    
    Hardware: Use a RGB LED Panel Wing connected to row D on the Papilio DUO and row C on the Papilio Pro.
    http://store.gadgetfactory.net/rgb-led-panel-wing/?page_context=category&faceted_search=0
    
    This sketch has been modified to display all of the GIF files you place in the smallFS directory instead of from an SD card. Press CTRL-K to bring up the sketch directory with the smallFS folder.
*/

#define circuit RGB_Matrix

#include <math.h>
#include <stdlib.h>
#include <SPI.h>
//#include <SD.h>
#include "FatFS.h"
#include "SmallFS.h"
#include <SmartMatrix_32x32.h>
#include "GIFDecoder.h"

#define DISPLAY_TIME_SECONDS 10

// range 0-255
//const int defaultBrightness = 255;
const int defaultBrightness = 15*(255/100);    // dim: 15% brightness

const rgb24 COLOR_BLACK = rgb24(0, 0, 0 );

// Smart Matrix instance
SmartMatrix matrix;

// Chip select for SD card on the SmartMatrix Shield
#define SD_CS WING_CH4
#define WISHBONESLOT 13

#define GIF_DIRECTORY "/gifs/"

int num_files;

void screenClearCallback(void) {
  matrix.fillScreen(COLOR_BLACK);
}

void updateScreenCallback(void) {
  matrix.swapBuffers();
}

void drawPixelCallback(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue) {
  //matrix.drawPixel(x, y, {red, green, blue});
  rgb24 color = rgb24(red, green, blue);
  matrix.drawPixel(x, y, color);  
}

// Setup method runs once, when the sketch starts
void setup() {

    setScreenClearCallback(screenClearCallback);
    setUpdateScreenCallback(updateScreenCallback);
    setDrawPixelCallback(drawPixelCallback);

    // Seed the random number generator
    //randomSeed(analogRead(14));
    randomSeed(1);

    Serial.begin(115200);
    
    if (SmallFS.begin()<0) {
    	Serial.println("No SmalLFS found.");
    }         

    // Initialize matrix
    matrix.begin(40);  //Updating every 40 milliseconds seems to work best.
    matrix.setBrightness(defaultBrightness);

    // Clear screen
    matrix.fillScreen(COLOR_BLACK);
    matrix.swapBuffers();

    // initialize the SD card at full speed
    pinMode(SD_CS, OUTPUT);

  SPI.begin();
  // put your setup code here, to run once:

  FatFS.begin(SPI, SD_CS);
  SPI.setClockDivider(SPI_CLOCK_DIV2);

    // Determine how many animated GIF files exist
//    num_files = enumerateGIFFiles(GIF_DIRECTORY, false);
//
//    if(num_files < 0) {
//        matrix.scrollText("No gifs directory", -1);
//        Serial.println("No gifs directory");
//        while(1);
//    }
//
//    if(!num_files) {
//        matrix.scrollText("Empty gifs directory", -1);
//        Serial.println("Empty gifs directory");
//        while(1);
//    }
}


void loop() {

    unsigned long futureTime;
    char pathname[64];
    char filename[64];

    //int index = random(num_files);
    
    SmallFSEntry e = SmallFS.getFirstEntry();

    // Do forever
    while (true) {
        // Can clear screen for new animation here, but this might cause flicker with short animations
        // matrix.fillScreen(COLOR_BLACK);
        // matrix.swapBuffers();

//        getGIFFilenameByIndex(GIF_DIRECTORY, index++, pathname);
//        if (index >= num_files) {
//            index = 0;
//        }

        if (e.hasNext())
          e++;
        else {
          e = SmallFS.getFirstEntry();
        }
          
        e.getName(filename);
        sprintf(pathname,"/smallfs/%s",filename);

        // Calculate time in the future to terminate animation
        futureTime = millis() + (DISPLAY_TIME_SECONDS * 1000);

        while (futureTime > millis()) {
            processGIFFile(pathname);
        }
    }
}
