#include <Arduino.h>
#include <appManager.h>
#include <displayManager.h>
#include <addresses.h>
#include <appManager.h>

// Libraries for Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Fonts/FreeSansBoldOblique9pt7b.h>
#include <Fonts/FreeSerifBold24pt7b.h>
#include <Fonts/FreeSerifBoldItalic9pt7b.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeMonoBoldOblique9pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>

appManager* appMgr;
 

// Other decration and implementation 


// constructor 

displayManager* displayManager_ctor(displayManager *const me) {    
   
    return me;
}

// Other Functions
 
 void setBackground(uint8_t b_color, uint8_t f_color, uint8_t x, uint8_t y, uint8_t w, uint8_t h, Adafruit_SH1106G* display_screen ) {  // background, foreground color and screen size (x,y ,w,h)
      display_screen->clearDisplay();
    //  display_screen->fillRect(x, y, w, h,SH110X_BLACK);
    // // delay(100);
      display_screen->setTextColor(f_color);
     // delay(100);
     Serial.print(F("Background Set \t"));
 }

 void setCursor(uint8_t x,uint8_t y, Adafruit_SH1106G* display_screen) {
     display_screen->setCursor(x,y);
     Serial.print(F("Cursor ("));
     Serial.print(x);
     Serial.print(F(","));
     Serial.print(y);
     Serial.print(F(")\t"));
 }

 void displayContent(uint8_t textSize, char * content, Adafruit_SH1106G* display_screen) { 
      
      display_screen->setTextColor(SH110X_WHITE);
      display_screen->setTextSize(textSize);
      display_screen->print(content);
      display_screen->display();
      Serial.println(F("Content displayed.."));

 }

 void displayBat_Level(uint8_t r_battery, uint8_t m_battery, Adafruit_SH1106G display_screen) {
   

   display_screen.setTextSize(1);
   display_screen.setCursor(5, 0);
   display_screen.print(F("  R BATTERY = "));
   display_screen.fillRect(84, 0, 30, 8,SH110X_BLACK);
   display_screen.setCursor(85, 1);
   display_screen.print(r_battery);
   display_screen.print(F("%"));
   display_screen.display();
   display_screen.setCursor(5, 56);
   display_screen.print(F("  M BATTERY = "));
   display_screen.fillRect(84, 55, 30, 10,SH110X_BLACK);
   display_screen.setCursor(85, 56);
   display_screen.print(m_battery);
   display_screen.print(F("%"));
   display_screen.display();
   delay(50);
 }


 void displayMenu(Adafruit_SH1106G display_screen) {
    
   display_screen.clearDisplay();
   display_screen.fillRect(5, 15, 30, 30,SH110X_WHITE);
   display_screen.setTextSize(2);
   display_screen.setTextColor(SH110X_BLACK);
   display_screen.setCursor(9,20);
   display_screen.print(F("M1"));
   
   display_screen.drawTriangle(27,43,11,43,19,35,SH110X_BLACK);
   display_screen.drawTriangle(25,42,13,42,19,36,SH110X_BLACK);
  
   display_screen.fillRect(47, 15, 30, 30,SH110X_WHITE);
   display_screen.setTextSize(2);
   display_screen.setTextColor(SH110X_BLACK);
   display_screen.setCursor(51,20);
   display_screen.print(F("M2"));
  // display.drawTriangle(69,43,53,43,61,35,SH110X_BLACK);
   //display.drawTriangle(67,42,55,42,61,36,SH110X_BLACK);
   display_screen.display();

   display_screen.fillRect(88, 15, 30, 30,SH110X_WHITE);
   display_screen.setTextSize(2);
   display_screen.setTextColor(SH110X_BLACK);
   display_screen.setCursor(92,20);
   display_screen.print(F("M3"));
  //display.drawTriangle(110,43,94,43,102,35,SH110X_BLACK);
  // display.drawTriangle(108,42,96,42,102,36,SH110X_BLACK);
   display_screen.display();


   display_screen.setTextSize(1);
   display_screen.setTextColor(SH110X_WHITE);
   display_screen.setCursor(2, 48);
   display_screen.print(F("--------------------"));
   display_screen.display();
  
   display_screen.setCursor(2, 7);
   display_screen.print(F("--------------------"));
   display_screen.display();
   delay(50);
  
   //Serial.println("Menu Displayed..");

 }

 void showSelection(displayManager* dispMgr, uint8_t selected_motor, Adafruit_SH1106G display_screen) {

  if(selected_motor==1)
  {
    //   display.fillCircle(display.width() / 2, display.height() / 2, i, SH110X_INVERSE);
    display_screen.drawTriangle(27,43,11,43,19,35,SH110X_BLACK);
    display_screen.drawTriangle(25,42,13,42,19,36,SH110X_BLACK);
    

    display_screen.drawTriangle(69,43,53,43,61,35,SH110X_WHITE);
    display_screen.drawTriangle(67,42,55,42,61,36,SH110X_WHITE);

    display_screen.drawTriangle(110,43,94,43,102,35,SH110X_WHITE);
    display_screen.drawTriangle(108,42,96,42,102,36,SH110X_WHITE);
    display_screen.display();
  
  } 

  if(selected_motor==2)
  {
   display_screen.drawTriangle(27,43,11,43,19,35,SH110X_WHITE);
   display_screen.drawTriangle(25,42,13,42,19,36,SH110X_WHITE);

   display_screen.drawTriangle(69,43,53,43,61,35,SH110X_BLACK);
   display_screen.drawTriangle(67,42,55,42,61,36,SH110X_BLACK);

   display_screen.drawTriangle(110,43,94,43,102,35,SH110X_WHITE);
   display_screen.drawTriangle(108,42,96,42,102,36,SH110X_WHITE);
   display_screen.display();
  }  


  if(selected_motor==3)
  {
   display_screen.drawTriangle(27,43,11,43,19,35,SH110X_WHITE);
   display_screen.drawTriangle(25,42,13,42,19,36,SH110X_WHITE);

   display_screen.drawTriangle(69,43,53,43,61,35,SH110X_WHITE);
   display_screen.drawTriangle(67,42,55,42,61,36,SH110X_WHITE);

   display_screen.drawTriangle(110,43,94,43,102,35,SH110X_BLACK);
   display_screen.drawTriangle(108,42,96,42,102,36,SH110X_BLACK);
   display_screen.display();
   
}
delay(500);
/*

  if(motor_sel==1)
   {
   d_val=m1_dam;
   }
    if(motor_sel==2)
   {
    d_val=m2_dam;
   }
    if(motor_sel==3)
   {
    d_val=m3_dam;
   }
}

*/
 }

void viewDampnessScreen(uint8_t value, uint8_t motor_sel, Adafruit_SH1106G display_screen) {


   display_screen.clearDisplay();
  
   display_screen.fillRect(5, 5, 100, 80,SH110X_WHITE);
   display_screen.setTextSize(2);
   
   display_screen.setCursor(40,7);
   display_screen.setTextSize(2);
   display_screen.setTextColor(SH110X_BLACK);
   display_screen.print(F("M"));
   display_screen.print(motor_sel);

   display_screen.setCursor(20,40);
   display_screen.setTextSize(2);
   display_screen.setTextColor(SH110X_BLACK); 
   display_screen.print(F("D="));
   display_screen.print(value);
   display_screen.display();
  
   delay(2000);

   /*
   
  
   
   display_screen.setTextSize(2);
   display_screen.setTextColor(SH110X_BLACK);
   display_screen.setCursor(9,20);
   display_screen.print("M1");
   */


}
