#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* https://e2e.ti.com/support/power-management-group/power-management/f/power-management-forum/742713/ev2300-evaluation-board-damaged-how-can-i-test*/
#include <stdlib.h>

// Custom Libraries
 #include "addresses.h"
 #include "appManager.h"
 #include "receiverBoard.h"


// Libraries for Implementation

#include <Wire.h>
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
      
        me->bat_conn_status = false;
        initBoard();
        resetCharger(me);

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

  // digitalWrite(heartbeat_LED,HIGH);
  // digitalWrite(Charging_LED_on,HIGH);
  // digitalWrite(Battery_LED,HIGH);
  // digitalWrite(Charge_full_LED,HIGH);
  // digitalWrite(button_pin,LOW);
}

void stopCharging(appManager* appMgr) {

  digitalWrite(v1_16_4,HIGH);
  digitalWrite(v1_16_6,HIGH);
  digitalWrite(v1_16_8,HIGH);

  digitalWrite(I1_3a,HIGH);
  digitalWrite(I1_4a,HIGH);
  digitalWrite(I1_6a,HIGH);

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

    if((appMgr->temp<=9)) {
       appMgr->temp_level =  TEMP_LEVEL_1;   

    } else if((appMgr->temp>9) && (appMgr->temp<=47)) {
       appMgr->temp_level =  TEMP_LEVEL_2;

    } else if((appMgr->temp>47) && (appMgr->temp<=54)) { 
       appMgr->temp_level =  TEMP_LEVEL_3;

    } else if((appMgr->temp>55)) {                    
       appMgr->temp_level =  TEMP_LEVEL_4;
    }
//Serial.println("Level set as per Temp...");    
}

void resetCharger(appManager* appMgr) {

   uint8_t bat_soc = appMgr->relative_soc;            // check battery charge status

   if((bat_soc<100) && !(bat_soc>101) ) {

   digitalWrite(Charge_full_LED,HIGH);    // OFF FULL_CHARGE LED

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
         resetCharger(appMgr);  
                       break;        
   
  }
//        digitalWrite(heartbeat_LED,HIGH); 
   
     setCurrent(appMgr);


      Serial.println(F("Charging set..")); 
      Serial.println(F("*********"));
      Serial.println();
 } else {

         digitalWrite(Charge_full_LED,LOW);
         digitalWrite(CHARGING_LED_ON,HIGH);
         stopCharging(appMgr);
         Serial.println(F("Battery is full.."));
   }
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
  //  Wire.setWireTimeout(2500,true);
    Wire.write(BATTERY_STATUS);
    reply = Wire.endTransmission(true);
    Wire.clearWriteError();
//    delay(10);
    if(reply== 5) {
      Serial.println(F("I2C timeout.."));
    }
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

float getTemp(appManager* appMgr) {
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
   
    do {
    Wire.setWireTimeout(2500,true);
    Wire.write(TEMPERATURE);
    reply = Wire.endTransmission(true);    
    Wire.clearWriteError();
 
    delay(10);
    } while(reply == 5);
    
    if(reply == 0) {
   
     appMgr->bat_conn_status = true;    // set boolean batteries connected
     Serial.print(F("Bat connected.."));
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

                appMgr->bat_conn_status = false;
                digitalWrite(BATTERY_LED,HIGH);
                digitalWrite(CHARGING_LED_ON,HIGH);
                digitalWrite(CHARGE_FULL_LED,HIGH);
                stopCharging(appMgr);
                Serial.println(F("Battery not connected.."));
                Serial.println(F("*********"));
                Serial.println();
    }
//     Serial.println("Collected Temp data...");
     Wire.flush();
     delay(10);  
     Wire.end();
//     digitalWrite(scl_pin,LOW);
}    
       
//     Wire.setWireTimeout(2500,false); 
     
     return ((float)myInt/10)-273;
}


/************ Scan ********/
void scan(appManager* appMgr) {

               blink();
               Serial.println(F("Scaning start.."));
               //screen.clearDisplay();
               appMgr->bat_conn_status = false;
               resetSavedValues(appMgr);

//               Wire.getWireTimeoutFlag();
               
//               Wire.begin();
 

                // Wire.beginTransmission(BAT_ADDRESS);
                // byte response = Wire.endTransmission();
                // Serial.println(response);
                appMgr->temp = getTemp(appMgr);  // Temparature                

//                Serial.println(appMgr->temp);
                if(appMgr->bat_conn_status) {
                           
                        //  temp = getTemp();  // Temparature                                                                               
                          // battery.voltage = getVolt();  // Voltage
                        
                          // battery.avgTimeToFull = getAvgTimeToFull();  // AVERAGE_TIME_TO_FULL
                         
                          // battery.remaingCapacity = getRemainingCapacity();   //  REMAINING_CAPACITY
                         
                          appMgr->relative_soc = getRelativeSOC(appMgr);  // RELATIVE_SOC                
                        
                          // battery.design_capacity = getDesignCapacity();  // DESIGN_CAPACITY
                                              
              //        }
                  
              //  }
              } else {
                // appMgr->connected_bat = false;
                // digitalWrite(BATTERY_LED,HIGH);
                // digitalWrite(CHARGING_LED_ON,HIGH);
                // digitalWrite(CHARGE_FULL_LED,HIGH);
                // Serial.println(F("Battery not connected.."));
                // Serial.println(F("*********"));
                // Serial.println();
              }            

//             Serial.println(" ");
//               Serial.println(F("Scaning done.."));


               delay(1000);
               blink();
         


//               digitalWrite(heartbeat_LED,HIGH);                  
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

       if((digitalRead(CHARGING_LED_ON) != LOW)) {


       if((charging_current <= CHARGING_VAL+5) && (charging_current >0) && (charging_current !=1 ) ) {               

          digitalWrite(CHARGING_LED_ON,LOW);
//          digitalWrite(BATTERY_LED,HIGH);   

       } else {

          if((charging_current >= NOT_CHARGING_VAL-5)) {

            if(appMgr->bat_conn_status) {
             digitalWrite(BATTERY_LED,LOW);
             }
           digitalWrite(CHARGING_LED_ON,HIGH);
           }
        }
       }

}






