#include <Arduino.h>


class Capteur_ultrason
{
public:
  Capteur_ultrason();
  long distanced(); 
  long distanceg();
private:
   const byte trigPind =3;
   const byte echoPind =2;
   const byte trigPing =6;
   const byte echoPing =5;
   const unsigned long MEASURE_TIMEOUT = 25000UL;
   const float SOUND_SPEED = 340.0 / 1000;
};
