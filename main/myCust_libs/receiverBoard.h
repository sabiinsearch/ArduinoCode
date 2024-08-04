// #include <Arduino.h>

#ifndef __RECEIVER_BOARD_H__
#define __RECEIVER_BOARD_H__

#define HEARBEAT_LED      7 // 13

#define VOLT_PIN_1        9
#define VOLT_PIN_2        10
#define VOLT_PIN_3        11

#define CURRENT_PIN_1     6
#define CURRENT_PIN_2     A1
#define CURRENT_PIN_3     A2

#define BUTTON_PIN        5

#define BATTERY_LED       4
#define CHARGING_LED_ON   3
#define CHARGE_FULL_LED   12

#define SDA               A4
#define SCL               A5

// constants for display
#define SCREEN_WIDTH            128 // OLED display width, in pixels
#define SCREEN_HEIGHT           64 // OLED display height, in pixels
#define OLED_RESET              4    //   QT-PY / XIAO

#define TEMP_DEFAULT       500
#define LEVEL_DEFAULT       10

#endif