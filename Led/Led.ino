#include <cvzone.h>

int bulb = 8;

SerialData serialData(1, 1); //(numOfValsRec,digitsPerValRec)
int valsRec[1]; // array of int with size numOfValsRec 

void setup() {
  serialData.begin();
  pinMode(bulb, OUTPUT);
  
  
}

void loop() {

  serialData.Get(valsRec);
  
  digitalWrite(bulb, valsRec[0]);
//  delay(1000);
//  digitalWrite(bulb, valsRec[1]);
//  delay(10);
}
