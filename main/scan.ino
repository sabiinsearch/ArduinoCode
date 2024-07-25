
enum temp_values {
  // CHARGER VALUES
TEMP_LEVEL_1,                 // 0 for 0-9
TEMP_LEVEL_2,                 // 1 for 19-47 
TEMP_LEVEL_3,                 // 2 for 48-54
TEMP_LEVEL_4,                 // 3 for 45-47
TEMP_LEVEL_5                  // Reset
};

float getTemp() {
//    Serial.println("Getting Temp data...");
    byte reply;
    byte byte_buffer[2];
    uint32_t myInt=0;
    // digitalWrite(scl_pin,LOW);
    // digitalWrite(sda_pin,LOW);
    
    Wire.beginTransmission(BAT_ADDRESS);

   // Wire.clearWireTimeoutFlag();
   
   bool flag = Wire.getWireTimeoutFlag();
    Wire.clearWireTimeoutFlag();
    // Serial.print(F("Flag: "));    
    // Serial.println(flag);
    
    // if(!flag) {
    //    return ((float)myInt/10)-273;
    // }

    if(!flag) {
    Wire.setWireTimeout(2500,true);
    Wire.write(TEMPERATURE);
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
      k++;
     }

     myInt = byte_buffer[0] + (byte_buffer[1] << 8);   // Least endian system
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

float getVolt() {
   
    byte byte_buffer[2];
    uint32_t myInt;
   
    Wire.beginTransmission(BAT_ADDRESS);   //  BAT_ADDRESS 
    Wire.write(VOLTAGE);
    Wire.endTransmission();
    delay(10);

     Wire.requestFrom(BAT_ADDRESS,sizeof(byte_buffer));
     int k=0;
     while(0 < Wire.available())
     {
      byte_buffer[k] = Wire.read();
      k++;
     }
     myInt = byte_buffer[0] + (byte_buffer[1] << 8);
       
//     Serial.print((float)myInt/1000);   // convert Mili Volt to Volt
     Serial.println("Collected Volt data...");
     return ((float)myInt/1000); 
}

unsigned int getAvgTimeToFull() {
    
    byte byte_buffer[2];
    uint32_t myInt;
    
    Wire.beginTransmission(BAT_ADDRESS);

    Wire.write(AVERAGE_TIME_TO_FULL); //  AVERAGE_TIME_TO_FULL

    Wire.endTransmission();
    delay(10);

     Wire.requestFrom(BAT_ADDRESS,sizeof(byte_buffer));

     int k=0;
     while(0 < Wire.available())
     {
      byte_buffer[k] = Wire.read();
      k++;
     }

     myInt = byte_buffer[0] + (byte_buffer[1] << 8);   // Least endian system
     Serial.println("Collected Avg Time to Full data...");
     return (unsigned int)myInt;
}

unsigned int getRemainingCapacity() {
    
    byte byte_buffer[2];
    uint32_t myInt;
    
    Wire.beginTransmission(BAT_ADDRESS);

    Wire.write(REMAINING_CAPACITY); //  AVERAGE_TIME_TO_FULL

    Wire.endTransmission();
    
    delay(10);
     Wire.requestFrom(BAT_ADDRESS,sizeof(byte_buffer));

     int k=0;
     while(0 < Wire.available())
     {
      byte_buffer[k] = Wire.read();
      k++;
     }

     myInt = byte_buffer[0] + (byte_buffer[1] << 8);   // Least endian system
    
     Serial.println("Collected Remaining Capacity...");
     return (unsigned int)myInt;
}

uint8_t getRelativeSOC() {

    byte byte_buffer[1];

    uint32_t myInt;

    Wire.beginTransmission(BAT_ADDRESS);

    Wire.write(RELATIVE_SOC);

    Wire.endTransmission();
    delay(10);
     Wire.requestFrom(BAT_ADDRESS,sizeof(byte_buffer));     
     while(0 < Wire.available())
     {
      //byte_buffer[k] = Wire.read();
      myInt = Wire.read();
//      Serial.print(myInt);            
     }
    // myInt = byte_buffer[0];//<<32+byte_buffer[0]<<24+byte_buffer[0]<<16+byte_buffer[0]<<8;
   //  myInt = byte_buffer[0] + (byte_buffer[1] << 8);   // Least endian system     
//     Serial.println(sizeof(byte_buffer));
     
     Serial.println("Collected Relative SoC...");
     return (uint8_t)myInt;
}


float getChargingVoltage() {

      
    byte byte_buffer[2];
    uint32_t myInt;
   
    Wire.beginTransmission(BAT_ADDRESS);
    Wire.write(CHARGING_VOLTAGE);
    Wire.endTransmission();
    delay(10);
     Wire.requestFrom(BAT_ADDRESS,sizeof(byte_buffer));
     int k=0;
     while(0 < Wire.available())
     {
      byte_buffer[k] = Wire.read();
      k++;
     }
//     myInt = byte_buffer[0] + (byte_buffer[1] << 8);
       myInt = byte_buffer[0] + byte_buffer[1];      
//     Serial.print((float)myInt/1000);   // convert Mili Volt to Volt
     
     return ((float)myInt/1000); 

}

int getDesignCapacity() {
         
    byte byte_buffer[2];
    uint32_t myInt;
    
         Wire.beginTransmission(BAT_ADDRESS);
         Wire.write(DESIGN_CAPACITY);
         Wire.endTransmission();
         delay(10);
         Wire.requestFrom(BAT_ADDRESS,sizeof(byte_buffer));

        int k=0;
        while(0 < Wire.available())
        {
         byte_buffer[k] = Wire.read();
         k++;
        }
          myInt = byte_buffer[0] + (byte_buffer[1] << 8);
          // Serial.print(F("Design Capacity received.."));
 //         Serial.println(myInt);
          
          Serial.println("Collected Design Capacity...");
          return myInt;           

}

void setLevel() {

    if((temparature<=9)) {
       temparature_level =  TEMP_LEVEL_1;   

    } else if((temparature>9) && (temparature<=47)) {
       temparature_level =  TEMP_LEVEL_2;

    } else if((temparature>47) && (temparature<=54)) { 
       temparature_level =  TEMP_LEVEL_3;

    } else if((temparature>55)) {                    
       temparature_level =  TEMP_LEVEL_4;
    }
//Serial.println("Level set as per Temp...");    
}

void setCharger() {
   
//   digitalWrite(heartbeat_LED,LOW);  

   switch(temparature_level) {
    
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

   }
//        digitalWrite(heartbeat_LED,HIGH); 
Serial.println(F("Charging set..")); 
Serial.println(F("*********"));
Serial.println();
}

void blink() {
  digitalWrite(HEARBEAT_LED,HIGH);
  delay(100);
  digitalWrite(HEARBEAT_LED,LOW); 
  delay(100);
}

void resetSavedValues() {
  temparature = 500;
  temparature_level = 10;
  Serial.println(F("Values reset.."));
  // Serial.print(F("T: "));
  // Serial.print(temparature);
  // Serial.print(F("  "));
  // Serial.print(F("Level: "));
  // Serial.println(temparature_level);
}

void scan() {
               blink();
               Serial.println(F("Scaning start.."));
               //screen.clearDisplay();
               bat_connected = false;
               resetSavedValues();

//               Wire.getWireTimeoutFlag();
               
//               Wire.begin();
 

                // Wire.beginTransmission(BAT_ADDRESS);
                // byte response = Wire.endTransmission();
                // Serial.println(response);
                temparature = getTemp();  // Temparature
//                Serial.println(temparature);
                if((temparature!=8) &&(temparature<100)) {

                       bat_connected = true;    // set boolean batteries connected
                       Serial.print(F("Bat connected.."));
                  // Get all connected battery data                                     

                        //  temp = getTemp();  // Temparature
                          
                          setLevel();  // set battery Level as per temparature
                           
                          // battery.voltage = getVolt();  // Voltage
                        
                          // battery.avgTimeToFull = getAvgTimeToFull();  // AVERAGE_TIME_TO_FULL
                         
                          // battery.remaingCapacity = getRemainingCapacity();   //  REMAINING_CAPACITY
                         
                          // battery.relative_soc = getRelativeSOC();  // RELATIVE_SOC                
                        
                          // battery.design_capacity = getDesignCapacity();  // DESIGN_CAPACITY
                                              
              //        }
                  
              //  }
              } else {
                bat_connected = false;
                Serial.println(F("Battery not connected.."));
                Serial.println(F("*********"));
                Serial.println();
              }            

//             Serial.println(" ");
//               Serial.println(F("Scaning done.."));


               delay(5000);
               blink();
         


//               digitalWrite(heartbeat_LED,HIGH);                  
}                                  
           

