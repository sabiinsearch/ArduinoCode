#ifndef __DISPLAY_MANAGER_H__
#define __DISPLAY_MANAGER_H__

#include <appManager.h>
#include <displayManager.h>
#include <Adafruit_SH110X.h>


typedef struct {

  Adafruit_SH1106G * screen;
  
} displayManager;


displayManager * displayManager_ctor(displayManager * const me); // constructor
void setBackground(uint8_t b_color, uint8_t f_color, uint8_t x, uint8_t y, uint8_t w, uint8_t h, Adafruit_SH1106G* display_screen);
void setCursor(uint8_t,uint8_t, Adafruit_SH1106G* display_screen);    // x,y
void displayContent(uint8_t, char *, Adafruit_SH1106G* display_screen);

#endif