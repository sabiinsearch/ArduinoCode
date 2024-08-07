#ifndef __ADDRESSES_H__
#define __ADDRESSES_H__

// I2C address
#define BAT_ADDRESS              0x0B
#define DISPLAY_ADDRESS          0x3C
#define SMB_ADDRESS              0x17
#define MUX_ADDRESS              0x70 // TCA9548A Encoders address

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
#define CHARGING_STATUS          0x55       // U2 word 
#define BATTERY_STATUS           0x16       // H2 word
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

#define CHARGING_MAX            150
#define CHARGING_MIN            80



#define bufferLen 32

/*
// CHARGER VALUES
#define TEMP_LEVEL_1              1   // 0-9
#define TEMP_LEVEL_2              2   // 9-47 
#define TEMP_LEVEL_3              3   // 48-54
#define TEMP_LEVEL_4              4   //45-47

*/

#endif