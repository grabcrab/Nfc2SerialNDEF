#include <Arduino.h>
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

#include "leds.h"

//comment #111 - github test

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
bool wasNfcError = false;

void setup(void) 
{
    Serial.begin(115200);
    Serial.println("NDEF Reader");
    initLeds();    
    ledStatus();
    Serial.println("NFC Reader Init...");
    if (!nfc.begin())
    {                
        ledInitError(DELAY_INIT_ERROR_MS);
        ESP.restart();
    }
    Serial.println("NFC init completed");
    ledHello(DELAY_HELLO_LED_MS);
}

void loop(void) 
{    
    ledStatus();
    wasNfcError = false;
    if (nfc.tagPresent())//TAG_WAIT_TIMEOUT
    {
        NfcTag tag = nfc.read();        
        if (tag.hasNdefMessage())
        {
            NdefMessage ndefMessage = tag.getNdefMessage();
            byte messCount = ndefMessage.getRecordCount();
            //Serial.println(messCount);
            for (int i = 0; i < messCount; i++)
            {
                const byte bufSize = 128;
                byte tmpBuf[bufSize];
                memset(tmpBuf, 0, bufSize);
                NdefRecord ndefRecord = ndefMessage.getRecord(i);
                ndefRecord.getPayload(tmpBuf);
                if (!wasNfcError)
                {
                    Serial.printf("%s\r\n", (char*) (tmpBuf+3));
                    ledTagWasRead(DELAY_TAG_READ_MS);
                    delay(DELAY_AFTER_READ_MS);
                }
                else 
                {   
                    ledTagReadError(DELAY_TAG_READ_ERROR_MS);
                }
            }
        }   
        else        
        {
            Serial.println("TAG WARNING: NO NDEF INFO!!!");
        }                
    }
}