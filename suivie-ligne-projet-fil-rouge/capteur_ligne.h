
#ifndef CAPTEUR_LIGNE_H
#define CAPTEUR_LIGNE_H

#include <Arduino.h>
#include <QTRSensors.h>

#ifdef DEBUG
    #define QTR_DEBUG
#endif

/*! \class Capteur_ligne
 * \brief classe representant le capteur de ligne QTR
 *
 *  La classe gère l'initialisation, la calibration et la lecture du capteur de ligne QTR
 */
class Capteur_ligne
{
public:
    Capteur_ligne();
    void Calibrate();
    int Read();
    QTRSensors qtr;
private:
    

    const uint8_t SensorCount = 8;
    uint16_t sensorValues[8];
};


#endif  // CAPTEUR_LIGNE_H
