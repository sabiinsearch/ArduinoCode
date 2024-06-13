void initBoard() {
  
  pinMode(v1_16_4,OUTPUT);
  pinMode(v1_16_6,OUTPUT);
  pinMode(v1_16_8,OUTPUT);
  pinMode(v2_16_4,OUTPUT);
  pinMode(v2_16_6,OUTPUT);
  pinMode(v2_16_8,OUTPUT);

  pinMode(I1_3a,OUTPUT);
  pinMode(I1_4a,OUTPUT);
  pinMode(I1_6a,OUTPUT);
  pinMode(I2_3a,OUTPUT);
  pinMode(I2_4a,OUTPUT);
  pinMode(I2_6a,OUTPUT); 

  pinMode(heartbeat_LED,OUTPUT);
  digitalWrite(heartbeat_LED,HIGH);

  digitalWrite(v1_16_4,LOW);
  digitalWrite(v1_16_6,LOW);
  digitalWrite(v1_16_8,LOW);
  digitalWrite(v2_16_4,LOW);
  digitalWrite(v2_16_6,LOW);
  digitalWrite(v2_16_8,LOW);

  digitalWrite(I1_3a,LOW);
  digitalWrite(I1_4a,LOW);
  digitalWrite(I1_6a,LOW);
  digitalWrite(I2_3a,LOW);
  digitalWrite(I2_4a,LOW);
  digitalWrite(I2_6a,LOW);
}

void resetCharger() {

//       digitalWrite(heartbeat_LED,LOW);

       digitalWrite(v1_16_4,LOW);
       digitalWrite(v1_16_6,LOW);
       digitalWrite(v1_16_8,LOW);
       digitalWrite(v2_16_4,LOW);
       digitalWrite(v2_16_6,LOW);
       digitalWrite(v2_16_8,LOW);

       digitalWrite(I1_3a,LOW);
       digitalWrite(I1_4a,LOW);
       digitalWrite(I1_6a,LOW);
       digitalWrite(I2_3a,LOW);
       digitalWrite(I2_4a,LOW);
       digitalWrite(I2_6a,LOW);  
      
//      digitalWrite(heartbeat_LED,HIGH);  
//       Serial.println(F("charger reset.."));  


}