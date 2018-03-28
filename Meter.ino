/*
 An example analogue meter using a ILI9341 TFT LCD screen

 This example uses the hardware SPI only and a board based
 on the ATmega328

 Needs Fonts 2, and 7 (also Font 4 if using large scale label)

 Comment out lines 153 and 197 to reduce needle flicker and
 to remove need for Font 4 (which uses ~8k of FLASH!)
 
 Alan Senior 23/2/2015
 */

// These are the connections for the UNO to display
#define sclk 13  // Don't change
#define mosi 11  // Don't change
#define cs   10  // If cs and dc pin allocations are changed then 
#define dc   9   // comment out #define F_AS_T line in "Adafruit_ILI9341_FAST.h"
                 // (which is inside "Adafriit_ILI9341_AS" library)

#define rst  7  // Can alternatively connect this to the Arduino reset

//#include <Adafruit_GFX_AS.h>     // Core graphics library
#include <MCUFRIEND_kbv.h> // Fast hardware-specific library
#include "AnalogMeter.h"
#include "adafruit_GFX_Ext.h"
MCUFRIEND_kbv tft;

Adafruit_GFX_Button Button;
#define LTBLUE    0xB6DF
#define LTTEAL    0xBF5F
#define LTGREEN         0xBFF7
#define LTCYAN    0xC7FF
#define LTRED           0xFD34
#define LTMAGENTA       0xFD5F
#define LTYELLOW        0xFFF8
#define LTORANGE        0xFE73
#define LTPINK          0xFDDF
#define LTPURPLE  0xCCFF
#define LTGREY          0xE71C

#define BLUE            0x001F
#define TEAL    0x0438
#define GREEN           0x07E0
#define CYAN          0x07FF
#define RED           0xF800
#define MAGENTA       0xF81F
#define YELLOW        0xFFE0
#define ORANGE        0xFD20
#define PINK          0xF81F
#define PURPLE    0x801F
#define GREY        0xC618
#define WHITE         0xFFFF
#define BLACK         0x0000

#define DKBLUE        0x000D
#define DKTEAL    0x020C
#define DKGREEN       0x03E0
#define DKCYAN        0x03EF
#define DKRED         0x6000
#define DKMAGENTA       0x8008
#define DKYELLOW        0x8400
#define DKORANGE        0x8200
#define DKPINK          0x9009
#define DKPURPLE      0x4010
#define DKGREY        0x4A49

  // Setup data buffer.
String inString;
int inByte = 0; // Incoming serial data byte.
int outputValue; // Sensor data to send to Processing.


float ltx = 0;    // Saved x coord of bottom of needle
uint16_t osx = 120, osy = 120; // Saved x & y coords
uint32_t updateTime = 0;       // time for next update
bool using_seril = true;
int old_analog =  -999; // Value last displayed
int old_digital = -999; // Value last displayed
int delay_ms = 0;
AnalogMeter anameter(&tft, 0, 0, 319, 149, 0, 200, "V", "Voltage");
void setup(void) {
  uint16_t ID = tft.readID(); //
  if (ID == 0xD3D3)
  { 
    ID = 0x9481; // write-only shield
  }
  tft.begin(ID);
  tft.setRotation(1);
  Serial.begin(9600);
  tft.fillScreen(BLACK);
  
//  analogMeter(); // Draw analogue meter
  
  anameter.Draw();
  anameter.plotNeedle(0,0); // Put meter needle at 0
  anameter.digitalMeter(138, 134+30); // Draw digital meter
  
  //Button.initButton(&tft, 120, 210, 100, 30, WHITE, GREY, BLACK, "HELLO", 2);
  //Scale.Draw();
  //Button.drawButton();
  updateTime = millis(); // Next update time
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  // Wait for serial port to connect. Needed for native USB port only.
  while (!Serial)
  {
    ; // Do nothing until connection established.
  }

  // Establish contact by sending initial data to Processing.
  // Loop on this until Processing responds by sending a request for sensor data.
  // Then start the loop().
  while (Serial.available() <= 0) // No data received.
  {
    Serial.println("0,0"); // Initial hello to Processing.
    Serial.flush();
    delay(500);
    if(millis()-updateTime > 1000)
    {
      using_seril = false;
      delay_ms = 1;
      break; 
     }
  }
}


void loop() {

  //Serial.println("I am alive");
  if (updateTime <= millis()) 
  {
    updateTime = millis() + 500;
    uint16_t read_data = analogRead(A5);
    int reading = 0;
    //reading = random(-50, 151); // Test with random value
    reading = map(read_data,0,0x3ff,0,5000); // Test with value form Analogue 0
    if (reading > 2000)
    {
      reading = 2000; 
     }
    anameter.showDigital(reading); // Update digital reading

    anameter.plotNeedle(reading/10, delay_ms); // Put meter needle at; // Update analogue meter, 8ms delay per needle increment
    if (Serial.available() > 0 && using_seril)
    {
      // Read serial data
      inByte = Serial.read();
      if (inByte > 0 && isDigit(inByte)) // Expecting a "1" from Processing.
      {
        inString = (char)inByte;
        //sensorNumber = inString.toInt();
  
        // read the analog voltage
        //sensorValue = read_data;
        // map it to the range of the analog out:
        outputValue = map(read_data, 0, 1023, 0, 255);
        // Send back the requested results
        Serial.print("1,");
        Serial.println(outputValue);

      }
    }
  }
}
