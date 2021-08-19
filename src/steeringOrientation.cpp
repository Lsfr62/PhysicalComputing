#include <Arduino.h>
int steeringOrientation(uint16_t);
int getNumbersOfZeros(uint16_t, int);
int lastMIddleOfLine = 0;
bool firstTimeMiddleOfLineIsMessured = true;
int thresholdForChange = 5;//Wenn MIddleOfLine um mehr als thresholdForChange verschoben werden soll, so wird geblockt.
int getSteeringAngle(uint16_t);

/**
 * Gets the positions in as int and gives back pin with higest chance of
 * 
 * @param gets 16 bits long number representing the sensor inputs: 0 = sensor sees white, 
 * 1=sensor sees black
 * @return returns an Angle between -35 and 35 that can be given to the servo Motor
*/
int getMiddleOfLine(uint16_t positions) {
  Serial.print(positions, BIN);
  Serial.print(" ");
  int nullen[16];
  int maxPos = -1;
  int maxNullen = -1;
  for(int i = 0; i < 16; i ++) {
    int n_i = positions & (1 << i);
    if(n_i == 0) {
        nullen[i] = getNumbersOfZeros(positions, i);
        if(maxNullen < nullen[i]) {
          maxNullen = nullen[i];
          maxPos = i;
        }
        i = i + nullen[i] - 1;

    }
  }
  int middleOfLine = maxPos + nullen[maxPos]/2;
  return middleOfLine;//(int) -map(middleOfLine, 2,13, -35, 35 );
 
}

int abs(int x) {
  if(x < 0) return -x;
  return x;
}


int steeringOrientation(uint16_t positions) {
  int middleOfLine = getMiddleOfLine(positions);

  /*if(firstTimeMiddleOfLineIsMessured) {
    firstTimeMiddleOfLineIsMessured = false;
    lastMIddleOfLine = middleOfLine;
    return middleOfLine;
  }

  if(abs(middleOfLine - lastMIddleOfLine) < 5){
    lastMIddleOfLine = middleOfLine;
    return middleOfLine;
  }

  return lastMIddleOfLine;*/
  return middleOfLine;
}


int getNumbersOfZeros(uint16_t positions, int i) {
  int erg = 1;
  //for(; erg < (16-i) && ((positions & (1<<erg) ) == 0); erg++) 
  while(erg < (16-i) && ((positions & ( 1 <<(i + erg)) ) == 0)) 
    erg++;
  
  return erg;

}



int getSteeringAngle(uint16_t positions) {
  int erg = steeringOrientation(positions);
  Serial.print(" ");
  Serial.print(erg);
  Serial.print(" ");
  return (int) -map(erg,5,14, -35, 35);
}
