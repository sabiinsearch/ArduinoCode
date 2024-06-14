#include <Adafruit_SH110X.h>
#include <splash.h>
#include <Wire.h>

// I2C address
#define BAT_ADDRESS              0x0B
#define DISPLAY_ADDRESS          0x3C
// constants for display
#define SCREEN_WIDTH            128 // OLED display width, in pixels
#define SCREEN_HEIGHT           64 // OLED display height, in pixels
#define OLED_RESET              4    //   QT-PY / XIAO

// Standard and common non-standard Smart Battery commands
#define BATTERY_MODE             0x03
#define TEMPERATURE              0x08       // U2 word         return in  0.1 K
#define VOLTAGE                  0x09       // U2 word         return in mV
#define CURRENT                  0x0A       // I2              return in mA
#define RELATIVE_SOC             0x0D       // U1 word         return in %
#define ABSOLUTE_SOC             0x0E       // U1 word         return in %
#define REMAINING_CAPACITY       0x0F       // U2 word         return mAh , cWh
#define RUN_TIME_TO_EMPTY        0x11       // U2 word         return min
#define FULL_CHARGE_CAPACITY     0x10       // U2 word         return min
#define AVERAGE_TIME_TO_EMPTY    0x12       // U2 word         return min
#define AVERAGE_TIME_TO_FULL     0x13       // U2 word         return min
#define CHARGING_CURRENT         0x14       // U2 word
#define CHARGING_VOLTAGE         0x15       // U2 word 
#define BATTERY_STATUS           0x16       // U2 word
#define CYCLE_COUNT              0x17
#define DESIGN_CAPACITY          0x18       // U2 Word
#define DESIGN_VOLTAGE           0x19
#define SPEC_INFO                0x1A
#define MFG_DATE                 0x1B
#define SERIAL_NUM               0x1C
#define MFG_NAME                 0x20      // String
#define DEV_NAME                 0x21      // String
#define CELL_CHEM                0x22      // String
#define MFG_DATA                 0x23      // String    Block-Mixed
#define MFG_DATA_2               0X44      // String
//#define MFG_DATA3B               0x4F    // String
//#define MFG_DATA3C               0x3C    // String
//#define MFG_DATA3D               0x3D    // String
//#define MFG_DATA3E               0x3E    // String
//#define MFG_DATA30               0x48    // String
//#define MFG_DATA31               0x49    // String
//#define MFG_DATA32               0x4A    // String
//#define MFG_DATA33               0x4B    // String
#define CELL8_VOLTAGE            0x43
#define CELL7_VOLTAGE            0x42
#define CELL6_VOLTAGE            0x41
#define CELL5_VOLTAGE            0x40
#define CELL4_VOLTAGE            0x3C   // Indidual cell voltages don't work on Lenovo and Dell Packs
#define CELL3_VOLTAGE            0x3D
#define CELL2_VOLTAGE            0x3E
#define CELL1_VOLTAGE            0x3F
#define STATE_OF_HEALTH          0x54

// constants for display
#define SCREEN_WIDTH            128 // OLED display width, in pixels
#define SCREEN_HEIGHT           64 // OLED display height, in pixels
#define OLED_RESET              4    //   QT-PY / XIAO

//Adafruit_SH1106G screen = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);  

// other variables

#define HEARBEAT_LED      7

#define VOLT_PIN_1        9
#define VOLT_PIN_2        10
#define VOLT_PIN_3        11

#define CURRENT_PIN_1     6
#define CURRENT_PIN_2     A1
#define CURRENT_PIN_3     A2

#define BUTTON_PIN        5

#define SDA               A4
#define SCL               A5

// battery variables

/*
struct battery_t{

//   uint8_t bat_portNo[2];
     uint8_t design_capacity;
//   const char* Manufacturer[2];
//   char* deviceName[2];
//   char* cellCem[2];
     float voltage;
     float temp;
     uint8_t temp_level;
     
     uint8_t avgTimeToFull;
     uint8_t remaingCapacity;
     uint8_t timeToEmpty;
     uint8_t avgTimeToEmpty;  
     uint8_t relative_soc; 
     uint8_t absolute_soc;
     float chargingVoltage;
};
*/

// init variables
bool bat_connected;
//battery_t battery;
uint8_t temp;
uint8_t temp_level;

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


Adafruit_SH1106G screen = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Wire.setClock(400000);
  initBoard();
  bat_connected = false;
  screen.begin(DISPLAY_ADDRESS,true);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(button_pin,LOW);
  delay(2);
  //if(!(digitalRead(button_pin)==HIGH)) {
    // Serial.print(F("Button: "));
    // Serial.println(digitalRead(button_pin));
     scan();
        
        if(!(bat_connected)) {

            refreshScreen();
            resetCharger();         

        }      
        else {
                 
                 printBatInfo();
                 setCharger();
                 displayOnScreen();
                       
//            delay(100);

//           Serial.println(F("Exiting main loop"));

            }                    
           for(uint8_t i=0;i<10;i++) {
              digitalWrite(heartbeat_LED,LOW);
               delay(100);
              digitalWrite(heartbeat_LED,HIGH);
               delay(100);
           }

   delay(4000);
  }
  // else{   
  //       Serial.print(F("Button: "));
  //       Serial.println(digitalRead(button_pin));
        
  //         for(uint8_t i=0;i<20;i++) {
  //             digitalWrite(heartbeat_LED,LOW);
  //              delay(100);
  //             digitalWrite(heartbeat_LED,HIGH);
  //              delay(100);
  //          }


