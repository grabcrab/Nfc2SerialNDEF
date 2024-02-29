#ifndef __LEDS_H__
#define __LEDS_H__

#include <Arduino.h>

#define LED_ON          true
#define LED_OFF         false

void initLeds(void);
void ledRed(bool state);
void ledGreen(bool state);
void ledBlue(bool state);
void ledWhite(bool state);
void ledsOff(void);
void beep(uint16_t ms);

void ledHello(uint16_t ms);
void ledInitError(uint16_t ms);
void ledTagWasRead(uint16_t ms);
void ledTagReadError(uint16_t ms);
void ledStatus(void);

#endif
