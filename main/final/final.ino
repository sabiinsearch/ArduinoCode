
//#include <Arduino.h>
#include <Adafruit_SH110X.h>
#include <splash.h>
#include <Wire.h>


// my libararies
 #include "libraries/myCust_libs/scanner.h"   //  "scanner.h"
//#include "scanner.h"
// #include "receiverBoard.h"
// #include "addresses.h"
#include "appManager.h"


appManager manager;
//Adafruit_SH1106G screen = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);  

// other variables


// battery variables

/*
struct battery_t{

//   uint8_t bat_portNo[2];
     uint8_t design_capacity;
//   const char* Manufacturer[2];
//   char* deviceName[2];
//   char* cellCem[2];
     float voltage;
     float temp;
     uint8_t temp_level;
     
     uint8_t avgTimeToFull;
     uint8_t remaingCapacity;
     uint8_t timeToEmpty;
     uint8_t avgTimeToEmpty;  
     uint8_t relative_soc; 
     uint8_t absolute_soc;
     float chargingVoltage;
};
*/






//Adafruit_SH1106G screen = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); 

/*********** initBoard */


/**** Blink*** */
 

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  
  appManager_ctor(&manager);

  initBoard();
  
  //screen.begin(DISPLAY_ADDRESS,true);
  
}

void loop() {
Serial.println(F("In loop..."));
     //  digitalWrite(CHARGING_LED_ON,LOW);
     //  delay(200);
     //  digitalWrite(CHARGING_LED_ON,HIGH);
     //  delay(200);

     //blink();       

     scan(&manager);

//    if((manager.chargingCurrent>150) || !(manager.connected_bat) ) {
//         digitalWrite(CHARGING_LED_ON,HIGH);     // switch off charging leds
// //        digitalWrite(CHARGING_LED_OFF,HIGH);
//      }    
         
        if(!(manager.connected_bat)) {

//            refreshScreen();
//            resetCharger();         
        }      
        else {
                                                  
                // resetCharger(&manager);
                 resetCharger();
                 printBatInfo(&manager); 
//                 displayOnScreet
//            delay(100);

//           Serial.println(F("Exiting main loop"));

            }                    

          //  for(uint8_t i=0;i<10;i++) {
          //     digitalWrite(heartbeat_LED,LOW);
          //      delay(100);
          //     digitalWrite(heartbeat_LED,HIGH);
          //      delay(100);
          //  }
        //  blink();

   delay(1000);
  }
  // else{   
  //       Serial.print(F("Button: "));
  //       Serial.println(digitalRead(button_pin));
        
  //         for(uint8_t i=0;i<20;i++) {
  //             digitalWrite(heartbeat_LED,LOW);
  //              delay(100);
  //             digitalWrite(heartbeat_LED,HIGH);
  //              delay(100);
  //          }


