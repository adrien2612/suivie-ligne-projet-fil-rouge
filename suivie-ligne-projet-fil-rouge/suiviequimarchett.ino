#include <md49.h>

#include <md49.h>
#include <Arduino.h>
#include "capteur_ultrason.h"
#include "capteur_ligne.h"
#include <QTRSensors.h>

QTRSensors qtr;
Capteur_ligne capteur;
Md49 md49_controleur(Serial1);
Capteur_ultrason ultra;

int val_enc1;
int val_enc2;
int vitesse=70; 
int pos1 = 0; 
int odo = 0;


const int STOP= 0;
const int PAUSE = 1; 
const int FOLLOW = 2; 
const int MESURE = 3; 
const int CALIBRER =4;

int Etat= CALIBRER; 




void setup() {
  Serial.begin(115200);
  Serial1.begin(9200);
  Serial3.begin(115200);

  //Serial3.print("et c'est partiiiii");


  md49_controleur.resetEncoder();
    while (Serial3.available() > 0) {
      char trash = Serial3.read();
    }
}


void loop() {
    Serial.println(Etat);
 
  switch (Etat){
    case CALIBRER: 
      calibrer();
    break;    
    case FOLLOW:
      suivie(); 
    break;
    case STOP: 
      arret();
    break;
    case PAUSE:
      pause();
    break;
    case MESURE:
      mesure();
    break;
  }
}




void suivie(){
     int pos = capteur.Read();
    Serial.println(pos);
    if ((pos==0) ||(pos==7000)){
      pos=pos1;
    }
    pos1=pos; 

    pos = (pos -3500)/150; 

    md49_controleur.setSpeed1(vitesse-pos);         
    md49_controleur.setSpeed2(vitesse+pos);

    Etat = MESURE;
}


void arret(){
    md49_controleur.stop();
}

void pause(){
    md49_controleur.stop();
    Etat = MESURE; 
}

void mesure(){
  val_enc1 = md49_controleur.getEncoder(1);
  val_enc2 = md49_controleur.getEncoder(2);
  Serial.println((val_enc1+val_enc2)/2);
  if ((val_enc1+val_enc2)/2 <  -1*odo*2.5){
    Etat= STOP; 
  }else{

  long distanced= ultra.distanced(); 
  long distanceg= ultra.distanceg(); 
  
  Serial.print(distanced);
  Serial.print (" "); 
  Serial.println(distanceg);
  
  if (((distanced <150) &&(distanced!=0)) or ((distanceg<150)&&(distanceg!=0))) {
    Etat= PAUSE ;
  }else{
    Etat = FOLLOW; 
  }
  }
}
void serialEvent3() {
  if(Serial3.available()) {
    char inChar =Serial3.read();
    Serial.print(inChar);
    if (inChar=='s'){
      Etat =PAUSE;
    }
    if (inChar=='z'){
      Etat =STOP;
    }
    if (inChar=='b'){
       odo = 23000;
       Serial.println(odo);
      Etat =PAUSE;
    }
  }
}

void calibrer() {
    if (Serial3.available() > 0) {
      char inChar = Serial3.read();
      Serial.print(inChar);
      if (inChar == 'a' ){
        Serial.println("Debut calibration");
        capteur.Calibrate();
        Serial.println("Fin calibration");
        Serial3.print('y');
        //char inChar = Serial3.read();
      Etat = STOP; 
      }
    }
     
}
