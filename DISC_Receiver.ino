#include "SPI.h"
#include "nRF24L01.h"
#include "RF24.h"
RF24 radio(7, 8); 
const byte address[6] = "00001";     

boolean SHOCK = 0;
#define SHOCK_TENS 5
#define SHOCK_STUN 6



void setup() 
{
    pinMode(SHOCK_TENS, OUTPUT);
    pinMode(SHOCK_STUN, OUTPUT);

    Serial.begin(9600);
    radio.begin();
    radio.openReadingPipe(0, address); 
    radio.setPALevel(RF24_PA_MIN);       
    radio.startListening();  
}

void loop() 
{
    if (radio.available())            
    {
    radio.read(&SHOCK, sizeof(SHOCK));   
    if(SHOCK == HIGH)
    {
    digitalWrite(SHOCK_TENS, HIGH);
    digitalWrite(SHOCK_STUN, HIGH);
    }
    else
    {
    digitalWrite(SHOCK_TENS, LOW);
    digitalWrite(SHOCK_STUN, LOW);
    }
    delay(5); 
    }
}
