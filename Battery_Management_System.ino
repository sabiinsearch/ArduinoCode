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

        if(!(manager.connected_bat)) {
          
            resetCharger();         
           // stopCharging();
        }      
        else {
              
              if(manager.relative_soc<100) {
               
               if(digitalRead(CHARGE_FULL_LED) == LOW) {
                  digitalWrite(CHARGE_FULL_LED,HIGH);
               }
                setCharger(&manager);  
               // digitalWrite(CHARGING_LED_ON,LOW);     
              }else {
               digitalWrite(CHARGE_FULL_LED,LOW);
               resetCharger();
               digitalWrite(CHARGING_LED_ON,HIGH);
              }
                           
                 printBatInfo(&manager); 
         }                    

          blink();

   delay(1000);
  }


