#include "capteur_ultrason.h"

Capteur_ultrason::Capteur_ultrason()
{
 pinMode(trigPind, OUTPUT);
 pinMode(echoPind, INPUT);
 pinMode(trigPing, OUTPUT);
 pinMode(echoPing, INPUT);
}

long Capteur_ultrason::distanced()
{
   
  float duration, distance;
  digitalWrite(trigPind, LOW);   
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPind, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPind, LOW);
  duration = pulseIn(echoPind, HIGH,MEASURE_TIMEOUT);
  distance = duration / 2.0 * SOUND_SPEED;
  return distance;
}

long Capteur_ultrason::distanceg()
{
   
  float duration, distance;
  digitalWrite(trigPing, LOW);
  delayMicroseconds(2); // Added this line 
  digitalWrite(trigPing, LOW);  // Added this line
  digitalWrite(trigPing, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPing, LOW);
  duration = pulseIn(echoPing, HIGH, MEASURE_TIMEOUT);
  distance = duration / 2.0 * SOUND_SPEED;
  return distance;
}
