#include "leds.h"

void initLeds(void)
{    
    pinMode(PIN_LED_RED, OUTPUT); 
    pinMode(PIN_LED_GREEN, OUTPUT);        
    pinMode(PIN_LED_BLUE, OUTPUT);    
    pinMode(PIN_BUZZER, OUTPUT);
    ledsOff();  
}

void ledRed(bool state)
{
  if (state) digitalWrite(PIN_LED_RED, HIGH);
  else digitalWrite(PIN_LED_RED, LOW);
}

void ledGreen(bool state)
{
  if (state) digitalWrite(PIN_LED_GREEN, HIGH);
  else digitalWrite(PIN_LED_GREEN, LOW);
}

void ledBlue(bool state)
{
  if (state) digitalWrite(PIN_LED_BLUE, HIGH);
  else digitalWrite(PIN_LED_BLUE, LOW);
}

void ledWhite(bool state)
{
    ledRed(state); 
    ledGreen(state);
    ledBlue(state);
}

void ledsOff(void)
{
    ledWhite(LED_OFF);
}

void startTone(void)
{
    digitalWrite(PIN_BUZZER, HIGH);
}

void stopTone(void)
{    
    digitalWrite(PIN_BUZZER, LOW);
}

void beep(uint16_t ms)
{    
    startTone();
    delay(ms);
    stopTone();
}

void ledHello(uint16_t ms)
{
    ledsOff();
    ledRed(LED_ON);
    delay(ms);
    ledRed(LED_OFF);
    ledGreen(LED_ON);
    delay(ms);
    ledGreen(LED_OFF);
    ledBlue(LED_ON);
    delay(ms);
    ledsOff();
    beep(ms/3);
}

void ledInitError(uint16_t ms)
{
    uint32_t startMs        = millis();
    const uint16_t onMs     = 100;
    const uint16_t offMs    = 300;
    ledsOff();
    while(millis() - startMs < ms)
    {
        ledRed(LED_ON);
        startTone();
        delay(onMs);
        ledRed(LED_OFF);
        stopTone();
        delay(offMs);
    }
    ledsOff();
}

void ledTagWasRead(uint16_t ms)
{
    //ledWhite(LED_ON);
    ledsOff();
    beep(ms/5);
    delay((ms/5)*4);    
}

void ledTagReadError(uint16_t ms)
{   
    ledsOff();
    ledRed(LED_ON);
    beep(ms/5);
    delay(ms/5);
    beep(ms/5);
    delay(ms/5);
    beep(ms/5);
    ledsOff();
}

void ledStatus(void)
{
    ledsOff();
    ledGreen(LED_ON);
}