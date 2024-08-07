#include <Wire.h>

// my libararies
#include "receiverBoard.h"
#include "addresses.h"
#include "appManager.h"


appManager manager;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  
  appManager_ctor(&manager);

  initBoard();
  
}

void loop() {

     blink();       

     scan(&manager);

        if(!(manager.connected_bat)) {      // Bat not Connected
          
            resetCharger();                     
           // stopCharging();
        }      
        else {l
              
              if((manager.relative_soc<100) && (manager.relative_soc>0)) {    // Bat Connected but SoC below 100
               
               if(digitalRead(CHARGE_FULL_LED) == LOW) {       // Check if Full_LED is already on
                  digitalWrite(CHARGE_FULL_LED,HIGH);
               }
                setCharger(&manager);  
               // digitalWrite(CHARGING_LED_ON,LOW);     
              }else {                                       // Bat Connected but SoC equal to or more than 100
               digitalWrite(CHARGE_FULL_LED,LOW);
               digitalWrite(CHARGING_LED_ON,HIGH);
               stopCharging();               
              }
                           
                 printBatInfo(&manager); 
         }                    

          blink();

   delay(1000);
  }


