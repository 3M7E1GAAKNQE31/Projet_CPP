#include "Buzzer.hpp"
#include <ESP8266WiFi.h>
#include <Arduino.h>


Buzzer::Buzzer()
{
    pinBuzzer=D6;
    init();
}
void Buzzer::init()
{
   pinMode(pinBuzzer, OUTPUT);
}
int Buzzer::Get_pin()
{
    return pinBuzzer;
}
void Buzzer::BuzzOn()
{
    tone(Get_pin(),500);
    delay(800);
}
void Buzzer::BuzzOff()
{
  noTone(Get_pin());
}
