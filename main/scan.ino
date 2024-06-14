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
    byte byte_buffer[2];
    uint32_t myInt;
   
    Wire.beginTransmission(BAT_ADDRESS);
    Wire.write(TEMPERATURE);
    Wire.endTransmission();
//    delay(10);
    Wire.requestFrom(BAT_ADDRESS,sizeof(byte_buffer));

     int k=0;
     while(0 < Wire.available())
     {
      byte_buffer[k] = Wire.read();
      k++;
     }

     myInt = byte_buffer[0] + (byte_buffer[1] << 8);   // Least endian system
     
//     Serial.println("Collected Temp data...");
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

    if((temp<=9)) {
       temp_level =  TEMP_LEVEL_1;   

    } else if((temp>9) && (temp<=47)) {
       temp_level =  TEMP_LEVEL_2;

    } else if((temp>47) && (temp<=54)) { 
       temp_level =  TEMP_LEVEL_3;

    } else if((temp>55)) {                    
       temp_level =  TEMP_LEVEL_4;
    }
//Serial.println("Level set as per Temp...");    
}

void setCharger() {
   
//   digitalWrite(heartbeat_LED,LOW);  

   switch(temp_level) {
    
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
}

void resetSavedValues() {
  temp = 0;
  temp_level=0;
}

void scan() {
                Wire.begin();
                screen.clearDisplay();
                bat_connected = false;
                resetSavedValues(); 

                Wire.beginTransmission(BAT_ADDRESS);
                byte response = Wire.endTransmission();
                Serial.println(response);
                
                if(response==0) {

                       bat_connected = true;    // set boolean batteries connected
                        Serial.println(F("Bat connected.."));
                  // Get all connected battery data                                     

                          temp = getTemp();  // Temparature
                          
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
              }            

//             Serial.println(" ");
               Serial.println(F("Scaning done.."));
               Wire.end();
//               digitalWrite(heartbeat_LED,HIGH);                  
}                                  
           

