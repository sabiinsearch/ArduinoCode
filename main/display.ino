
void displayOnScreen() {

//  Serial.println(F("Display.."));
//  digitalWrite(heartbeat_LED,LOW); 

  if(!(bat_connected)) {
   screen.clearDisplay();
   delay(2);
   screen.setCursor(10,35);
   screen.setTextColor(SH110X_WHITE);
   screen.setTextSize(2);
   screen.print(F("Waiting.."));

  } else {
       screen.clearDisplay(); 
       delay(2);
       screen.setTextSize(1);
       screen.setTextColor(SH110X_WHITE);
       screen.setCursor(5,5);
       screen.print(F("Battery Status\n"));
    
       uint32_t i=0;
             
       uint8_t x=30;
       uint8_t y =(i*15)+20;

          // Serial.print(F("No. of Batteries: "));       
          // Serial.print(appMgr->connected_bat);
          // Serial.print(F("\ti: "));  
          // Serial.print(i);
          // Serial.print(F("\tx: "));
          // Serial.print(x);
          // Serial.print(F("\ty: "));
          // Serial.println(y);

           screen.setCursor(x,y);
           screen.print("T");
           screen.setCursor(x+10,y);
           screen.print(temparature);


           screen.setCursor(x+1,y+10);
           screen.print("L");
           screen.setCursor(x+10,y+10);
           screen.print(temparature_level);
           
           // appMgr->displayMgr->screen->print(F("Bat@"));
           //appMgr->displayMgr->screen->print(i+1);

           //appMgr->displayMgr->screen->print(appMgr->bat_portNo[i]);
           //appMgr->displayMgr->screen->setCursor(x+30,y);
           //appMgr->displayMgr->screen->print("Cap:");
           //appMgr->displayMgr->screen->setCursor(x+38,y);
           //appMgr->displayMgr->screen->print(appMgr->design_capacity[i]);

           // set the cursor to zero
           x=y=-1;
           
    //   appMgr->displayMgr->screen->print(appMgr->Manufacturer);
   //           screen->display();
    }
   screen.display();
   delay(2);

//   digitalWrite(heartbeat_LED,HIGH);
 
}

void printBatInfo() {

//          digitalWrite(heartbeat_LED,LOW);  
          // Serial.print(F("Bat: "));
          // Serial.print(i+1);       
          // Serial.print(F("  volt: "));       
          // Serial.print(appMgr->voltage[i]);
           Serial.print(F("  T:"));
           Serial.print(temparature);

           Serial.print(F("   L:"));
           Serial.println(temparature_level);

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

void refreshScreen () {

//digitalWrite(heartbeat_LED,LOW);  

screen.clearDisplay();
   delay(2);
   screen.setCursor(10,35);
   screen.setTextColor(SH110X_WHITE);
   screen.setTextSize(2);
   screen.print(F("Waiting.."));
   screen.display();
   delay(2);

 //   digitalWrite(heartbeat_LED,HIGH);   
//   Serial.println(F("Screen refreshed.."));

   /*
          appMgr->displayMgr->screen->clearDisplay(); 
       delay(2);
       appMgr->displayMgr->screen->setTextSize(1);
       appMgr->displayMgr->screen->setTextColor(SH110X_WHITE);
       appMgr->displayMgr->screen->setCursor(5,5);
       appMgr->displayMgr->screen->print(F("Battery Status\n"));
   */

}
