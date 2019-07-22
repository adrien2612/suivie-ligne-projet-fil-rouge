
#include "capteur_ligne.h"

Capteur_ligne::Capteur_ligne()
{
  sensorValues[SensorCount];

  // configure the sensors
  qtr.setTypeRC();
  
  qtr.setSensorPins((const uint8_t[]){25, 27, 31, 35, 37, 38, 40, 42}, SensorCount);

  qtr.setEmitterPin(2);
}

void Capteur_ligne::Calibrate()
{
  // 2.5 ms RC read timeout (default) * 10 reads per calibrate() call
  // = ~25 ms per calibrate() call.
  // Call calibrate() 400 times to make calibration take about 10 seconds.
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
}


int Capteur_ligne::Read()
{
  // read calibrated sensor values and obtain a measure of the line position
  // from 0 to 7000 (for a white line, use readLineWhite() instead)
  uint16_t position = qtr.readLineBlack(sensorValues);
  return position;

}
