// This example shows various featues of the library for LCD with 16 chars and 2 lines.
// NuMaker UNO nuc131 / Arduino 1.8.15
// library LiquidCrystal_PCF8574 at version 2.2.0 in
// nuvoton\hardware\nuvoton\2.3.4\libraries\Wire
// hardware\\nuvoton\\2.3.4\\variants
// c:\Users\Nuvoton\AppData\Local\Arduino15\
// c:\*****\*******\AppData\Local\Arduino15\

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 4 line display

int show = -1;

// 2 custom characters

byte dotOff[] = { 0b00000, 0b01110, 0b10001, 0b10001,
                  0b10001, 0b01110, 0b00000, 0b00000 };
byte dotOn[] = { 0b00000, 0b01110, 0b11111, 0b11111,
                 0b11111, 0b01110, 0b00000, 0b00000 };
//RGB LED=================================================
const int lowestPin = 0;
const int highestPin = 3;
int rgbLed[]={ 2, 3, 4 };  /* R, G, B LED */
//RGB LED=================================================



void setup() {
  int error;
//RGB LED=================================================
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  for (int thisPin =lowestPin; thisPin <= highestPin; thisPin++)  
  pinMode(rgbLed[thisPin], OUTPUT); 

  pinMode(5, OUTPUT); 
//RGB LED=================================================
  Serial.begin(115200);
  Serial.println("LCD...");

  // wait on Serial to be available on Leonardo
  while (!Serial)
    ;

  Serial.println("Probing for PCF8574 on address 0x27...");

  // See http://playground.arduino.cc/Main/I2cScanner how to test for a I2C device.
  Wire.begin();
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);

  if (error == 0) {
    Serial.println(": LCD found.");
    show = 0;
    lcd.begin(20, 4);  // initialize the lcd

    lcd.createChar(1, dotOff);
    lcd.createChar(2, dotOn);

  } else {
    Serial.println(": LCD not found.");
  }  // if

}  
// end setup()
//=================================================================================

void loop() {
//RGB LED=================================================
// start RGB led
  // iterate over the pins:
  for (int thisPin =lowestPin; thisPin <= highestPin; thisPin++) { 
    // fade the LED on thisPin from off to brightest:
    for (int brightness = 0; brightness < 255; brightness++) {
      analogWrite(rgbLed[thisPin], brightness);
      delay(2);
    } 
    // fade the LED on thisPin from brithstest to off:
    for (int brightness = 255; brightness >= 0; brightness--) {
      analogWrite(rgbLed[thisPin], brightness);
      delay(2);
    } 
    // pause between LEDs:
    delay(100);
 }
//end RGB led 
//RGB LED=================================================
 
  if (show == 0) {
    lcd.setBacklight(255);
    lcd.home();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("*   HELLO WORLD    *");
    lcd.setCursor(0, 1);
    lcd.print("*   NuMaker UNO    *");
    lcd.setCursor(0, 2);
    lcd.print("* ================ *");    
    lcd.setCursor(0, 3);
    lcd.print("*  LCD type 2004A  *");    
    delay(200);

    lcd.setBacklight(0);
    delay(100);
    lcd.setBacklight(255);
    delay(500);

  } else if (show == 1) {
    lcd.clear();
    lcd.print("Cursor On");
    lcd.cursor();

  } else if (show == 2) {
    lcd.clear();
    lcd.print("Cursor Blink");
    lcd.blink();

  } else if (show == 3) {
    lcd.clear();
    lcd.print("Cursor OFF");
    lcd.noBlink();
    lcd.noCursor();

  } else if (show == 4) {
    lcd.clear();
    lcd.print("Display Off");
    lcd.noDisplay();

  } else if (show == 5) {
    lcd.clear();
    lcd.print("Display On");
    lcd.display();

  } else if (show == 7) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("***     LCD      ***");
    lcd.setCursor(0, 1);
    lcd.print("*   NuMaker UNO    *");
    lcd.setCursor(0, 3);
    lcd.print("* demo @bwginfo.ro *");
    
  } else if (show == 8) {
    lcd.scrollDisplayLeft();
  } else if (show == 9) {
    lcd.scrollDisplayLeft();
  } else if (show == 10) {
    lcd.scrollDisplayLeft();
  } else if (show == 11) {
    lcd.scrollDisplayRight();

  } else if (show == 12) {
    lcd.clear();
    lcd.print("write-");

  } else if (show == 13) {
    lcd.clear();
    lcd.print("custom 1:<\01>");
    lcd.setCursor(0, 1);
    lcd.print("custom 2:<\02>");

  } else {
    lcd.print(show - 13);
  }  // if

  delay(400);
  show = (show + 1) % 16;
 
}  // loop()

