#include "steeringOrientation.h"

int lastMIddleOfLine = 0;
bool firstTimeMiddleOfLineIsMessured = true;
int thresholdForChange = 5;//Wenn MIddleOfLine um mehr als thresholdForChange verschoben werden soll, so wird geblockt.
const int historyLength = 10;
int errorMiddleOfLineHistory[historyLength];
int middleOfLineHistoryPointer = 0;
unsigned long currentTime, previousTime;

int getMiddleOfLine(uint16_t positions) {
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
  return middleOfLine;
}

int getLastMiddleOfLine(){
  return lastMIddleOfLine;
}

int abs(int x) {
  if(x < 0) return -x;
  return x;
}

/**
 * Gives the sensor in the middle of the line
 * @param positions represents the sensor data in a sequence of 1 and 0
 * @return returns the middle of the line. Calculates that a really big change from one messurement to the next is not realistic
*/
int steeringOrientation(uint16_t positions) {
  int middleOfLine = getMiddleOfLine(positions);
  if(firstTimeMiddleOfLineIsMessured) { //initialisierung beim ersten durchlauf
    firstTimeMiddleOfLineIsMessured = false;
    lastMIddleOfLine = middleOfLine;
    return middleOfLine;
  }

  if(abs(middleOfLine - lastMIddleOfLine) < 5){
    lastMIddleOfLine = middleOfLine;
    return middleOfLine;
  }
  

  return lastMIddleOfLine;
}

/**
* gives back length of sequence of zeros from a given starting position. Example
* 1110000101 <- the third digit is a 1 and is followed by 4 zeros in a row. So the function call with position 3 would return 4. Not 5, because there is a 1 seperating the in total 5 zeros
* @param positions represents the sensor data in a sequence of 1 and 0, @param i is place in sequence to look at
* @return length of sequence of zeros from a given starting position
*/
int getNumbersOfZeros(uint16_t positions, int i) {
  int erg = 1;
  //for(; erg < (16-i) && ((positions & (1<<erg) ) == 0); erg++) 
  while(erg < (16-i) && ((positions & ( 1 <<(i + erg)) ) == 0)) 
    erg++;
  
  return erg;
}

/**
* Gives angle for servo
* @param positions represents the sensor data in a sequence of 1 and 0
* @return an angle between -35 an d 35 degree, ready to give to the servo
*/
int getSteeringAngle(uint16_t positions) {
  int sO = steeringOrientation(positions);
  /*
  *------------------------------------------------------------------------------------
  *Versuch für PID Regler
  *------------------------------------------------------------------------------------
  currentTime = millis();
  
  int realMiddleOfLine = (8 - 1); //da es 16 Pins sind => also pins von 0 bis 15 => Mitte ist (8 - 1)
  errorMiddleOfLineHistory[middleOfLineHistoryPointer] = sO - realMiddleOfLine;
  int error = errorMiddleOfLineHistory[middleOfLineHistoryPointer];
  double K_P = 2;
  double K_I = 5;
  double K_D = 1;
  double dt = (double)(currentTime - previousTime);

  double sum = 0;
  for(int i = 0; i < historyLength; i++) {
    sum += errorMiddleOfLineHistory[ ( middleOfLineHistoryPointer - i + historyLength) % historyLength];
  }
  double D = (error - errorMiddleOfLineHistory[(middleOfLineHistoryPointer - 1 + historyLength) % historyLength]) / dt;



  previousTime = currentTime; 
  //middleOfLineHistory = (middleOfLineHistory+1) % historyLength;
  int offset = -10;

  return K_P * error + K_I* sum + K_D* D + offset;
  *------------------------------------------------------------------------------------
  *Ende PID
  *------------------------------------------------------------------------------------
  */
  return (int) -map(sO, 5, 14, -35, 35);

}
