#include <Stepper.h>
int boardx = 2500;
int boardy = 4000;

int zU = A3;
int zD = A4;
int vect[] = {0,3,82,8};
const int stepsPerRevolution = 2048;
Stepper stepperX = Stepper(stepsPerRevolution, 5, 3, 4, 2);;
Stepper stepperY = Stepper(stepsPerRevolution, 11, 9, 10, 8);
Stepper stepperZ = Stepper(stepsPerRevolution, A11, A9, A10, A8);
#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin

int xValue = 0; 
int yValue = 0; 
int zUC = 0;
int zDC = 0;

void setup() {
  stepperX.setSpeed(12);
  stepperY.setSpeed(12);
  stepperZ.setSpeed(12);
  pinMode(zD,INPUT_PULLUP);
  pinMode(zU,INPUT_PULLUP);
  pinMode(13,OUTPUT);
  Serial.begin(9600) ;
}

void loop() {
  
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
  //Serial.println(xValue);
//  Serial.print("    ");
//  Serial.println(yValue);
  zUC = digitalRead(zU);
  zDC = digitalRead(zD);
  if(zUC == 0){
    stepperZ.step(1);
    digitalWrite(13, HIGH);
    
    }
  else if (zDC == 0){
    stepperZ.step(-1); 
    digitalWrite(13, LOW);
  }
  
  if(xValue > 900 ){
    stepperY.step(-1);
   //Serial.println("yay");
  }
  else if(xValue < 100){
    stepperY.step(1);
   // Serial.println("yayyayysyayaysdy8");
  }
//
  if(yValue > 900){
    stepperX.step(-1);
  }
  else if(yValue < 100){
    stepperX.step(1);
  }
}
