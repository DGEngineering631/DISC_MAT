#include "SoftwareSerial.h"
#include "SPI.h"
#include "nRF24L01.h"
#include "RF24.h"
RF24 radio(7, 8); 
const byte address[6] = "00001";     
boolean SHOCK = 0;

#define GREEN_LED 6
#define RED_LED 5
#define BUZZER 3
int PRESSURE_PIN = A1;
int PRESSURE_VALUE = 0;
int PRESSURE_VALUE_THRES = 400;
int i = 0;
int TIMER_i = 0;


void setup() 
{
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    
    Serial.begin(9600);

    radio.begin();                 
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN); 
    radio.stopListening();  
}

void loop() 
{
  i =0;
  TIMER_i = 0;
  digitalWrite(BUZZER,1);
  PRESSURE_VALUE = analogRead(PRESSURE_PIN);
  Serial.println(PRESSURE_VALUE);
  if(PRESSURE_VALUE > PRESSURE_VALUE_THRES)
  {
  i = 1;
  while(i == 1)
    {
    PRESSURE_VALUE = analogRead(PRESSURE_PIN);
    if(PRESSURE_VALUE > PRESSURE_VALUE_THRES)
      {  
        digitalWrite(GREEN_LED,1);
         if(TIMER_i < 25)
          {
            TIMER_i = TIMER_i + 1;
            delay(1000);
            Serial.print(TIMER_i);
          }
        else if(TIMER_i >= 25 && TIMER_i < 30)
          {
            digitalWrite(RED_LED,1);
            delay(500);
            digitalWrite(RED_LED,0);
            delay(500);
            TIMER_i = TIMER_i + 1;
            Serial.print(TIMER_i);
          }
        else if(TIMER_i >= 30)
          {
            digitalWrite(RED_LED,1);
            delay(500);
            digitalWrite(BUZZER,0);
            delay(500);
            digitalWrite(BUZZER,1);
            TIMER_i = TIMER_i + 1;
            SHOCK = HIGH;
            radio.write(&SHOCK, sizeof(SHOCK));          
          }
      }
      else
      {
        i = 0;
      }
    }
  }
  else
  {
    digitalWrite(GREEN_LED,0);
    digitalWrite(RED_LED,0);
    digitalWrite(BUZZER,1);
    SHOCK = LOW;
    radio.write(&SHOCK, sizeof(SHOCK));
  }
  delay(5);
}
