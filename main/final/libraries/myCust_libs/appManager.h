#ifndef __APP_MANAGER_H__
#define __APP_MANAGER_H__

// #include "stdio.h"
#include "string.h"

// Custom Libraries
  #include "displayManager.h"
  #include "Adafruit_SH110X.h"
// #include "app_config.h"
// #include "connectionManager.h"
// #include "motorManager.h"
// #include "receiverBoard.h"

/*Application Manager's attributes*/

enum temp_values {
  // CHARGER VALUES
TEMP_LEVEL_1,                 // 0 for 0-9
TEMP_LEVEL_2,                 // 1 for 19-47 
TEMP_LEVEL_3,                 // 2 for 48-54
TEMP_LEVEL_4,                 // 3 for 45-47
TEMP_LEVEL_5                  // Reset
};

typedef struct {

     // battery info
  
     uint8_t connected_bat;
//     uint8_t bat_portNo[2];
     uint8_t design_capacity[2];
     const char* Manufacturer[2];
     char* deviceName[2];
     char* cellCem[2];
     float voltage[2];
     float temp;
     uint8_t temp_level;
     
     uint16_t avgTimeToFull[2];
     uint16_t remaingCapacity[2];
     uint16_t timeToEmpty[2];
     uint16_t avgTimeToEmpty[2];  
     uint8_t relative_soc; 
     uint8_t absolute_soc[2];
     float chargingVoltage[2];
     unsigned int chargingCurrent;
     
     displayManager * displayMgr;
        
} appManager;


void appManager_ctor(appManager * const me); // constructor
void initBoard();
void tcaselect(uint8_t);  // for setting MUX channel
void scan(appManager* appMgr);
void blink();

char * getDeviceName(appManager*);
char * getCellChemistry(appManager*);
void getBatteryMode(appManager*);
float getTemp(appManager*);
float getVolt(appManager*);
void getManufactureDate(appManager*);
unsigned int getAvgTimeToFull(appManager*);
unsigned int getAvgTimeToEmpty(appManager*);
unsigned int getRemainingCapacity(appManager*);
unsigned int getRuntimeToEmpty(appManager*);
uint8_t getRelativeSOC(appManager*);
unsigned int getAbsoluteSOC(appManager*);
uint8_t getChargingCurrent(appManager*);
int getDesignCapacity(appManager*);
void printBatInfo(appManager*);
void displayOnScreen(appManager*);
void refreshScreen(appManager*);
appManager* getManager(appManager*);
void setVolt(appManager*,uint8_t);
void setCurrent(appManager*);
void setLevel(appManager*);
void resetCharger(appManager*);
void setCharger_volt_current(appManager*);
void stopCharging(appManager*);

#endif