void initBoard() {
  
  pinMode(v1_16_4,OUTPUT);
  pinMode(v1_16_6,OUTPUT);
  pinMode(v1_16_8,OUTPUT);

  pinMode(I1_3a,OUTPUT);
  pinMode(I1_4a,OUTPUT);
  pinMode(I1_6a,OUTPUT);

  pinMode(sda_pin,INPUT);
  pinMode(scl_pin,INPUT);

//  pinMode(button_pin,OUTPUT);
  // digitalWrite(button_pin,LOW);

  pinMode(heartbeat_LED,OUTPUT);
  digitalWrite(heartbeat_LED,HIGH);

  digitalWrite(v1_16_4,LOW);
  digitalWrite(v1_16_6,LOW);
  digitalWrite(v1_16_8,LOW);


  digitalWrite(I1_3a,LOW);
  digitalWrite(I1_4a,LOW);
  digitalWrite(I1_6a,LOW);

}

void resetCharger() {

//       digitalWrite(heartbeat_LED,LOW);

       digitalWrite(v1_16_4,LOW);
       digitalWrite(v1_16_6,LOW);
       digitalWrite(v1_16_8,LOW);


       digitalWrite(I1_3a,LOW);
       digitalWrite(I1_4a,LOW);
       digitalWrite(I1_6a,LOW);

//      digitalWrite(heartbeat_LED,HIGH);  
//       Serial.println(F("charger reset.."));  


}