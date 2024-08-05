#include <stdio.h>
#include <string.h>
#include <stdint.h>


// https://e2e.ti.com/support/power-manags

// Custom Libraries

 #include "addresses.h"
 #include "appManager.h"
 #include "receiverBoard.h"


// Libraries for Implementation

#include <Wire.h>
#include <SPI.h>

// init variables
bool bat_connected;
//battery_t battery;
// static uint8_t temparature=500;
// static uint8_t temparature_level;
static float charging_current;

int scl_pin = SCL;
int sda_pin = SDA;

int heartbeat_LED = HEARBEAT_LED;
int button_pin = BUTTON_PIN;
//Voltage pins for battery

int v1_16_4 = VOLT_PIN_1;
int v1_16_6 = VOLT_PIN_2;
int v1_16_8 = VOLT_PIN_3;

// Current pins for battery1

 int I1_3a = CURRENT_PIN_1;
 int I1_4a = CURRENT_PIN_2;
 int I1_6a = CURRENT_PIN_3;

// Charging Idicators

int Charging_LED_on  = CHARGING_LED_ON;
int Battery_LED      = BATTERY_LED;
int Charge_full_LED  = CHARGE_FULL_LED;

//#include "Adafruit_SH110X.h"
// #include <EEPROM.h>
//#include <MPU6050.h>

//#define SDA_PORT PORTC

//variables

 

/* constructor implementation */

void appManager_ctor(appManager * const me) {
      
        me->connected_bat = false;
        initBoard();
        resetCharger();

//        Serial.println("Board Initialized and charger reset \n");

//        me->connected_bat == 0;
//        me->displayMgr = displayManager_ctor(&dispMgr);

  

//       display.display();
//       delay(1000);

//   // Clear the buffer.
//      display.clearDisplay();

//   delay(500); 
//   display.clearDisplay();
  
//   me->displayMgr->screen = &display;  

// //     display.display();
//       me->displayMgr->screen->clearDisplay(); 
//       delay(500);
      
//       me->displayMgr->screen->clearDisplay(); 
//       me->displayMgr->screen->display();
//       Serial.println(F("Manager with displayManager initialized..\n"));

}

void printBatInfo(appManager* appMgr) {

//          digitalWrite(heartbeat_LED,LOW);  
          // Serial.print(F("Bat: "));
          // Serial.print(i+1);       
          // Serial.print(F("  volt: "));       
          // Serial.print(appMgr->voltage[i]);
           Serial.print(F("  T:"));
           Serial.print(appMgr->temp);

           Serial.print(F("   L:"));
           Serial.print(appMgr->temp_level);

           Serial.print(F("   SoC:"));
           Serial.print(appMgr->relative_soc);

           Serial.print(F("   Charging_Current:"));
           Serial.println(appMgr->chargingCurrent);

           
          // Serial.print(F("  Capacity: "));
          // Serial.print(appMgr->design_capacity[i]);
          // Serial.print(F(" mA"));

          // Serial.print(F("  Remaining: "));
          // Serial.print(appMgr->remaingCapacity[i]);
          // Serial.print(F(" mA"));
          // Serial.print(F("  Time To Full: "));
          // Serial.print(appMgr->avgTimeToFull[i]);
          // Serial.print(F(" min"));
          // Serial.print(F("  Relative SOC: "));
          // Serial.print(appMgr->relative_soc[i]);
          // Serial.println(F(" %"));
//            digitalWrite(heartbeat_LED,HIGH);  

}

appManager* getManager(appManager* appMgr) {
  return appMgr;
}


void initBoard() {
  
  pinMode(v1_16_4,OUTPUT);
  pinMode(v1_16_6,OUTPUT);
  pinMode(v1_16_8,OUTPUT);

  pinMode(I1_3a,OUTPUT);
  pinMode(I1_4a,OUTPUT);
  pinMode(I1_6a,OUTPUT);

  pinMode(sda_pin,OUTPUT);
  pinMode(scl_pin,OUTPUT);

  pinMode(Charging_LED_on,OUTPUT);
  pinMode(Battery_LED,OUTPUT);
  pinMode(Charge_full_LED,OUTPUT);

  pinMode(heartbeat_LED,OUTPUT);
//  pinMode(button_pin,OUTPUT);


  digitalWrite(v1_16_4,LOW);
  digitalWrite(v1_16_6,LOW);
  digitalWrite(v1_16_8,LOW);


  digitalWrite(I1_3a,LOW);
  digitalWrite(I1_4a,LOW);
  digitalWrite(I1_6a,LOW);

  digitalWrite(heartbeat_LED,HIGH);
  digitalWrite(Charging_LED_on,HIGH);
  digitalWrite(Battery_LED,HIGH);
  digitalWrite(Charge_full_LED,HIGH);
  // digitalWrite(button_pin,LOW);
}

void stopCharging() {

  digitalWrite(v1_16_4,LOW);
  digitalWrite(v1_16_6,LOW);
  digitalWrite(v1_16_8,LOW);

  digitalWrite(I1_3a,LOW);
  digitalWrite(I1_4a,LOW);
  digitalWrite(I1_6a,LOW);

}

void blink() {
  
  digitalWrite(HEARBEAT_LED,HIGH);
//  digitalWrite(CHARGING_LED_OFF,LOW);
//  digitalWrite(CHARGING_LED_ON,LOW);
  delay(100);
  digitalWrite(HEARBEAT_LED,LOW); 
//  digitalWrite(CHARGING_LED_OFF,HIGH);
//  digitalWrite(CHARGING_LED_ON,HIGH);
  delay(100);
}

void setLevel(appManager* appMgr) {

    if((DUMMY_LEVEL < 5) && (appMgr->temp<=9)) {
       appMgr->temp_level =  TEMP_LEVEL_1;   

    } else if((DUMMY_LEVEL < 5) && (appMgr->temp>9) && (appMgr->temp<=47)) {
       appMgr->temp_level =  TEMP_LEVEL_2;

    } else if((DUMMY_LEVEL < 5) && (appMgr->temp>47) && (appMgr->temp<=54)) { 
       appMgr->temp_level =  TEMP_LEVEL_3;

    } else if((DUMMY_LEVEL < 5) && (appMgr->temp>55)) {                    
       appMgr->temp_level =  TEMP_LEVEL_4;
    }
     
    if((DUMMY_LEVEL>5)) {
        Serial.print(F("Dummy Level set.."));
        appMgr->temp_level = DUMMY_LEVEL;
     }
//Serial.println("Level set as per Temp...");    
}

void setCharger(appManager* appMgr) {

 // if(appMgr->relative_soc<100) {

   setLevel(appMgr);  // set battery Level as per temparature
//   digitalWrite(heartbeat_LED,LOW);  

   switch(appMgr->temp_level) {
    
    case TEMP_LEVEL_1:

         digitalWrite(v1_16_6, LOW);
         digitalWrite(v1_16_8, LOW);
             delay(10);
         digitalWrite(v1_16_4, HIGH);

         digitalWrite(I1_4a, LOW);
         digitalWrite(I1_6a,LOW);
             delay(10);
         digitalWrite(I1_3a, HIGH);

                      break;
    case TEMP_LEVEL_2:

         digitalWrite(v1_16_4, LOW);
         digitalWrite(v1_16_8, LOW);
             delay(10);
         digitalWrite(v1_16_6, HIGH);

         digitalWrite(I1_3a, LOW);
         digitalWrite(I1_6a,LOW);
             delay(10);
         digitalWrite(I1_4a, HIGH);    

                       break;
    case TEMP_LEVEL_3:

         digitalWrite(v1_16_4, LOW);
         digitalWrite(v1_16_6, LOW);
             delay(10);
         digitalWrite(v1_16_8, HIGH);

         digitalWrite(I1_3a, LOW);
         digitalWrite(I1_4a,LOW);
             delay(10);
         digitalWrite(I1_6a, HIGH);  

                      break;
    case TEMP_LEVEL_4:

         digitalWrite(v1_16_4, LOW);
         digitalWrite(v1_16_6, LOW);          
         digitalWrite(v1_16_8, LOW);

         digitalWrite(I1_3a, LOW);
         digitalWrite(I1_4a,LOW);             
         digitalWrite(I1_6a, LOW);  

                      break;
    case TEMP_LEVEL_5:
         resetCharger();  
                       break;    
    case DUMMY_LEVEL:

           if(DUMMY_LEVEL==6) {
              digitalWrite(v1_16_4, LOW);
              digitalWrite(v1_16_6, LOW);          
              digitalWrite(v1_16_8, LOW);

              digitalWrite(I1_3a, LOW);
              digitalWrite(I1_4a, LOW);             
              digitalWrite(I1_6a, LOW);  
           }

           if(DUMMY_LEVEL==7) {
              digitalWrite(v1_16_4, HIGH);
              digitalWrite(v1_16_6, LOW);          
              digitalWrite(v1_16_8, LOW);

              digitalWrite(I1_3a, HIGH);
              digitalWrite(I1_4a, LOW);             
              digitalWrite(I1_6a, LOW);  
           }

           if(DUMMY_LEVEL==8) {
              digitalWrite(v1_16_4, LOW);
              digitalWrite(v1_16_6, HIGH);          
              digitalWrite(v1_16_8, LOW);

              digitalWrite(I1_3a, LOW);
              digitalWrite(I1_4a, HIGH);             
              digitalWrite(I1_6a, LOW);  
           }

           if(DUMMY_LEVEL==9) {
              digitalWrite(v1_16_4, LOW);
              digitalWrite(v1_16_6, LOW);          
              digitalWrite(v1_16_8, HIGH);

              digitalWrite(I1_3a, LOW);
              digitalWrite(I1_4a, LOW);             
              digitalWrite(I1_6a, HIGH);  
           }
          break;
           

  }
//        digitalWrite(heartbeat_LED,HIGH);     
   
      setCurrent(appMgr);
   
      Serial.println(F("Charging set..")); 
      Serial.println(F("*********"));
      Serial.println();
  //  }  
  //  else {
  //       digitalWrite(CHARGE_FULL_LED,LOW);
  //       digitalWrite(CHARGING_LED_ON,HIGH);
  //       Serial.println(F("Battery is full.."));
  // }  
 } 

/**********resetValues**********/
void resetSavedValues(appManager* appMgr) {
   appMgr->temp = TEMP_DEFAULT;
   appMgr->temp_level = LEVEL_DEFAULT;
   appMgr->chargingCurrent = 0;
  // Serial.print(F("T: "));
  // Serial.print(temparature);
  // Serial.print(F("  "));
  // Serial.print(F("Level: "));
  // Serial.println(temparature_level);
   Serial.println(F("Values reset.."));  
}
/************    RELATIVE_SOC   *******************/

uint8_t getRelativeSOC(appManager* appMgr) {

    byte byte_buffer[2];

    uint32_t myInt;

    Wire.beginTransmission(BAT_ADDRESS);

    Wire.write(RELATIVE_SOC);

    Wire.endTransmission();

     Wire.requestFrom(BAT_ADDRESS,sizeof(byte_buffer));
     int k=0;
     while(0 < Wire.available())
     {
      byte_buffer[k] = Wire.read();
      k++;
     }
     myInt = byte_buffer[0];
     return (uint8_t)myInt;
}
/*********************         CHAGRING CURRENT    *****************/ 
uint8_t getChargingCurrent(appManager* appMgr) {
    byte reply;    
    byte byte_buffer[1];
    unsigned int myFloat;
  
         digitalWrite(scl_pin,LOW);
         digitalWrite(sda_pin,LOW);

         Wire.beginTransmission(BAT_ADDRESS);
        
         Wire.clearWireTimeoutFlag();
   
         bool flag = Wire.getWireTimeoutFlag();
         Wire.clearWireTimeoutFlag();
    // if(!flag) {
    //    return ((float)myInt/10)-273;
    // }

    if(!flag) {
      int while_loop_counter = 0;   // counter to confirm battery not connected..
    do {

    while_loop_counter++;  
    
    Wire.setWireTimeout(2500,true);
    Wire.write(BATTERY_STATUS);
    reply = Wire.endTransmission(true);    
    Wire.clearWriteError(); 
    delay(10);

      if((while_loop_counter>40) && (reply !=0)) {

                appMgr->connected_bat = false;
                digitalWrite(BATTERY_LED,HIGH);
                digitalWrite(CHARGING_LED_ON,HIGH);
                digitalWrite(CHARGE_FULL_LED,HIGH);
                stopCharging();
                // Serial.println(F("Battery not connected.."));
                // Serial.println(F("*********"));
                // Serial.println();

    }
    } while(reply != 0);

      while_loop_counter = 0;

    if(reply == 0) {
      Wire.requestFrom(BAT_ADDRESS,sizeof(byte_buffer));

      int k=0;
      while(0 < Wire.available())
      {
         byte_buffer[k] = Wire.read();
//         Serial.print(byte_buffer[k],HEX);
//         Serial.print(F(" "));
         k++;
      }
      Serial.println();
      //myFloat = byte_buffer[0] + (byte_buffer[1] << 8);   // Least endian system
      myFloat = byte_buffer[0];
    }


         Wire.flush();
         delay(10);  
         Wire.end();
         digitalWrite(scl_pin,LOW);

        int k=0;
        while(0 < Wire.available())
        {
         byte_buffer[k] = Wire.read();
         k++;
        }
          myFloat = byte_buffer[0] + (byte_buffer[1] << 8);
          return myFloat;           
    }
} 

float getTemp(appManager* appMgr, uint8_t counter) {
//    Serial.println("Getting Temp data...");
    byte reply=5;
    byte byte_buffer[2];
    uint32_t myInt=0;
    // digitalWrite(scl_pin,LOW);
    // digitalWrite(sda_pin,LOW);
    
    Wire.beginTransmission(BAT_ADDRESS);

   // Wire.clearWireTimeoutFlag();
   
   bool flag = Wire.getWireTimeoutFlag();

    Wire.clearWireTimeoutFlag();

    if(!flag) {

    int while_loop_counter = 0;   // counter to confirm battery not connected..

    while(reply != 0) {

      while_loop_counter++;  
    
      Wire.setWireTimeout(2500,true);
      Wire.write(TEMPERATURE);
      reply = Wire.endTransmission(true);    
      Wire.clearWriteError(); 
      delay(20);

    };
     

     if((reply !=0) && (while_loop_counter>40)) {

                appMgr->connected_bat = false;
                digitalWrite(BATTERY_LED,HIGH);
                digitalWrite(CHARGING_LED_ON,HIGH);
                digitalWrite(CHARGE_FULL_LED,HIGH);
                stopCharging();
                // Serial.println(F("Battery not connected.."));
                // Serial.println(F("*********"));
                // Serial.println();

    }    
      
    if((reply == 0) && (counter=0)) {
    
     Serial.println(F("Bat connected.."));
    
    }else if((reply == 0) && (counter>0))  {
      Serial.print(F("."));
    }
    
    appMgr->connected_bat = true;    // set boolean batteries connected  
    digitalWrite(BATTERY_LED,LOW);                 
                  // Get all connected battery data          

    Wire.requestFrom(BAT_ADDRESS,sizeof(byte_buffer));

     int k=0;
     while(0 < Wire.available())
     {
      byte_buffer[k] = Wire.read();
      k++;
     }

     myInt = byte_buffer[0] + (byte_buffer[1] << 8);   // Least endian system
    } else {


    }
//     Serial.println("Collected Temp data...");
     Wire.flush();
     delay(10);  
     Wire.end();
//     digitalWrite(scl_pin,LOW);       
//     Wire.setWireTimeout(2500,false); 
     
     return ((float)myInt/10)-273;
}


/************ Scan ********/
void scan(appManager* appMgr) {

               float temp_temp=-1;

               blink();

               Serial.println(F("Scaning start.."));

               appMgr->connected_bat = false;

               resetSavedValues(appMgr);
                              
                 temp_temp = getTemp(appMgr,0);  // Temparature                
             
                 if(appMgr->connected_bat) {
                        uint8_t while_counter = 0;

                        while((temp_temp>150) || (temp_temp<0)) {   // store valid temp value
                          temp_temp = getTemp(appMgr,while_counter++);                           
                          delay(50); 
                        }
                          appMgr->temp = temp_temp;
                          temp_temp=0;

                          appMgr->relative_soc = getRelativeSOC(appMgr);  // RELATIVE_SOC                

              } else {
                   digitalWrite(BATTERY_LED,HIGH);
              }            

               delay(1000);
               blink();
                       
}

void tcaselect(uint8_t i) {
   //if(i<7) return;
   Wire.beginTransmission(MUX_ADDRESS);
   Wire.write(1<<i);
   Wire.endTransmission();
}


void setVolt(appManager* appMgr,uint8_t state) {

   switch(state) {
        
   }

}


void setCurrent(appManager* appMgr) {

       uint8_t charging_current = getChargingCurrent(appMgr);   
           
       appMgr->chargingCurrent = charging_current;              // Save to variable for later access               

       if((digitalRead(CHARGING_LED_ON) != LOW) && ((charging_current<CHARGING_MAX) && (charging_current>CHARGING_MIN))) {               

          digitalWrite(CHARGING_LED_ON,LOW);
//          digitalWrite(BATTERY_LED,HIGH);   

       } else {
          if (!((charging_current<CHARGING_MAX) && (charging_current>CHARGING_MIN))) { 
            digitalWrite(CHARGING_LED_ON,HIGH);
          }
          // if((charging_current >= NOT_CHARGING_VAL) || (charging_current<10)) {

          //   if(appMgr->connected_bat) {
          //    digitalWrite(BATTERY_LED,LOW);
          //    }
          //  digitalWrite(CHARGING_LED_ON,HIGH);
          //  Serial.println(F("Not Charging.."));
          //  }
        }

}
 
 void resetCharger() {
        
  digitalWrite(v1_16_4,LOW);
  digitalWrite(v1_16_6,LOW);
  digitalWrite(v1_16_8,LOW);

  digitalWrite(I1_3a,LOW);
  digitalWrite(I1_4a,LOW);
  digitalWrite(I1_6a,LOW);

 }





