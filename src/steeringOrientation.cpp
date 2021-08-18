#include <Arduino.h>
int steeringOrientation(uint16_t);
int getNumbersOfZeros(uint16_t, int);

/**
 * Processes the sensor input into the angle the servo has to adjust to
 * 
 * @param gets 16 bits long number representing the sensor inputs: 0 = sensor sees white, 
 * 1=sensor sees black
 * @return returns an Angle between -35 and 35 that can be given to the servo Motor
*/
int steeringOrientation(uint16_t positions) {
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
  return (int) -map(middleOfLine, 2,13, -35, 35 );
 //gelb, rot, rot, orange, gelb, grün, blau, magenta, grau ,lila
}


int getNumbersOfZeros(uint16_t positions, int i) {
  int erg = 1;
  //for(; erg < (16-i) && ((positions & (1<<erg) ) == 0); erg++) 
  while(erg < (16-i) && ((positions & ( 1 <<(i + erg)) ) == 0)) 
    erg++;
  
  return erg;

}

