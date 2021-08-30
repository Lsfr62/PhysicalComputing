#include "reflectanceSensor.h"

const int numberOfSensors = 16;
int sensors[numberOfSensors];
int messwerte[numberOfSensors];
int threshold[numberOfSensors]; //jeder Sensor braucht einen individuellen Wert, um beste Ergebnisse zu bringen
void ausgabe();
void waitTillEnter();
void saveThresholdsToROM();
void readThresholdsFromROM();
bool isIn(int, int, int);
int counterSinceLastOrthogonalLineLeft = -1; //Es werden immer zwei Querlienien hinterinenander abgefahren. Um die Zeit dazwischen zu messen, wird dieser Counter eingeführt
int counterSinceLastOrthogonalLineRight = -1; //Es werden immer zwei Querlienien hinterinenander abgefahren. Um die Zeit dazwischen zu messen, wird dieser Counter eingeführt
int counterSinceLastOrthogonalLine = -1; //Es werden immer zwei Querlienien hinterinenander abgefahren. Um die Zeit dazwischen zu messen, wird dieser Counter eingeführt

/**
 * Gets data from sensor
 * 
 * @return integer of 16 Bits, where 1 = black, white = 0
 * 
 * Example function call: 
 * Serial.println((int)getSensorData(), BIN);
 * 
 * Warning: also returns 0, if sensor is not found
*/
uint16_t getSensorData() {
    sensorUpdate();
    int16_t erg = 0;
    for(int i = 0; i < numberOfSensors; i++) {
        if (messwerte[i] < 1) erg = erg + (0 << i);
        else erg = erg + (1 << i);
    }
    return erg;
} 

/**
 * Store measurements in messwerte[] array.
*/
void sensorUpdate()
{
    for (int i = 0; i < numberOfSensors; i++)
    {
        if (threshold[i] <= 0)
            continue;
        pinMode(sensors[i], OUTPUT);    
        digitalWrite(sensors[i], HIGH); 
        delayMicroseconds(15);
        pinMode(sensors[i], INPUT); 
        delayMicroseconds(threshold[i]); //mehr 0-en => Zahl runter, mehr 1-er => Zahl hoch
        messwerte[i] = digitalRead(sensors[i]);
        delayMicroseconds(500);
    }
    //ausgabe(); //output makes sence, when you want to check, if the pins are correctly linked
    
}

/**
 * prepares sensors for usage
*/
void sensorSetup()
{
    EEPROM.begin(numberOfSensors);
    
    for(int i = 0; i < numberOfSensors; i ++) {
        Serial.print(i);
        Serial.print(":");
        Serial.print(EEPROM.read(i));
        Serial.println(" ");
    }
    for (int i = 0; i < numberOfSensors; i++)
    {
        sensors[i] = -1;
        messwerte[i] = -1;
        threshold[i] = -1;
    }

   
    sensors[1 - 1] = 0;
    sensors[2 - 1] = 2;
    sensors[3 - 1] = 4; 
    sensors[4 - 1] = 16;
    sensors[5 - 1] = 17;
    sensors[6 - 1] = 5;
    sensors[7 - 1] = 18;
    sensors[8 - 1] = 35;
    sensors[9 - 1] = 32;
    sensors[10 - 1] = 33;
    sensors[11 - 1] = 25;
    sensors[12 - 1] = 26;
    sensors[13 - 1] = 27;
    sensors[14 - 1] = 14;
    sensors[15 - 1] = 12;
    sensors[(16 - 1)] = 13;
    
    

    
    readThresholdsFromROM();
    
    /*
    Historical: 
    Thresholds has been added manually in code as magic numbers. There was no calibration method
    //too many 0-en => number down, too many  1-er => number up
    threshold[0] = -1;//!
    threshold[1] = 390;
    threshold[2] = 530;
    threshold[3] = 325;
    threshold[4] = 365;
    threshold[5] = 380;
    threshold[6] = 480;
    threshold[7] = -1;
    threshold[8] = 420;
    threshold[9] = 380;
    threshold[10] = 510;
    threshold[11] = 420;
    threshold[12] = 425;
    threshold[13] = 455;
    threshold[14] = 555;
    threshold[15] = 710;
    */
    
}


/**
 * Measures thresholds for every sensor after enter-key is pressed
*/
void callibriereThreshold()
{

/*
    In German:
  Der Threshold ist eine Zahl, die für jeden Sensor einzelnt bestimmt werden muss.
  Dafür werden für jeden Sensor einzelnt Werte ausprobiert. Dafür werden alle
  Werte nacheinander durch gegangen. Zunächst wird ein oberer 
  Grenzwert bestimmt (Supremum-Threshold), der eigentliche Threshold-Wert liegt gewiss darunter.
  Dann wird ein unterer Grenzwet bestimmt (Infimum-Threshold), der eignetliche Threshold-Wert 
  liegt gewiss darüber. Dann wird das arithmetische Mittel dieser Zahlen als 
  Threshold gespeichert. Alle Daten werden in Arrays gespeichert;
  infimumThresholds[3] entspricht der unteren Grenze für den Sensor 4 (4, da wir 3+1 rechnen müssen).
*/


    int supremumThresholds[numberOfSensors];
    int infimumThresholds[numberOfSensors];
    for (int i = 0; i < numberOfSensors; i++)
    {
        supremumThresholds[i] = -1;
        infimumThresholds[i] = -1;
    }
    Serial.println("Halte Sensor auf schwarz und drücke Enter.");
    waitTillEnter();
    Serial.println("Kallibriere schwarz...");
    for (int i = 0; i < numberOfSensors; i++)
    {
        if (sensors[i] < 0) continue;
        int steps = 10; //10
        int triggerLimit = 0;
        int testLimit = 4;
        for (int thresholdTry = 0; thresholdTry < 10000; thresholdTry = thresholdTry + steps)
        {
            pinMode(sensors[i], OUTPUT);    //pinModeAll(OUTPUT);
            digitalWrite(sensors[i], HIGH); //digitalWrite(ioLine, HIGH);
            delayMicroseconds(15);
            pinMode(sensors[i], INPUT);      //pinMode(ioLine, INPUT);
            delayMicroseconds(thresholdTry); //mehr 0-en => Zahl runter, mehr 1-er => Zahl hoch
            if (digitalRead(sensors[i]) == 0){
                triggerLimit++;
            }
            if (digitalRead(sensors[i]) == 1)
                triggerLimit = 0;
            if (triggerLimit == testLimit)
            { // es soll drei mal hintereinander eine 0 gemessen worden sein
                supremumThresholds[i] = thresholdTry;
                break;
            }
            delayMicroseconds(500);
            if (10000 - steps - steps / 2 < thresholdTry)
            {
                Serial.print("Pin");
                Serial.print(i);
                Serial.println("does not callibrate");
            }
        }
    }
    Serial.println("Fertig mit schwartz");
    Serial.println("Supremums for threshold:");

    for (int i = 0; i < numberOfSensors; i++)
    {
        Serial.print(i);
        Serial.print(":");
        Serial.print(supremumThresholds[i]);
        Serial.print(", ");
    }
    //--------------- beginne, inf zu kallibrieren

    Serial.println("\nHalte Sensor auf weiß und drücke Enter");
    waitTillEnter();
    Serial.println("Kallibriere weiß...");
    for (int i = 0; i < numberOfSensors; i++)
    {
        if (sensors[i] < 0)
            continue;
        int steps = 10;
        int how_often_do_we_have_a_1_in_a_row = 0;
        int testLimit = 4;
        for (int thresholdTry = supremumThresholds[i]; thresholdTry > 0; thresholdTry = thresholdTry - steps)
        {
            pinMode(sensors[i], OUTPUT);    
            digitalWrite(sensors[i], HIGH); 
            delayMicroseconds(15);
            pinMode(sensors[i], INPUT);     
            delayMicroseconds(thresholdTry); //mehr 0-en => Zahl runter, mehr 1-er => Zahl hoch
            if (digitalRead(sensors[i]) == 1)
                how_often_do_we_have_a_1_in_a_row++;
            if (digitalRead(sensors[i]) == 0)
                how_often_do_we_have_a_1_in_a_row = 0;
            if (how_often_do_we_have_a_1_in_a_row == testLimit)
            { // es soll so oft hintereinander eine 0 gemessen worden sein
                infimumThresholds[i] = thresholdTry;
                break;
            }
            delayMicroseconds(500);

            if (5000 - steps - steps / 2 < thresholdTry)
            {
                Serial.print("Pin");
                Serial.print(i);
                Serial.println("does not callibrate");
            }
        }
    }
    Serial.println("Fertig mit weiß");
    Serial.println("Infimum for threshold:");

    for (int i = 0; i < numberOfSensors; i++)
    {
        Serial.print(i);
        Serial.print(":");
        Serial.print(infimumThresholds[i]);
        Serial.print(", ");
    }

    for (int i = 0; i < numberOfSensors; i++)
    {
        if (sensors[i] < 0)
            continue;
        threshold[i] = (supremumThresholds[i] + infimumThresholds[i]) / 2;
    }

    Serial.println("\nThresholds:");

    for (int i = 0; i < numberOfSensors; i++)
    {
        Serial.print(i);
        Serial.print(":");
        Serial.print(threshold[i]);
        Serial.print(", ");
    }
    saveThresholdsToROM();
    Serial.println("\nIm ROM Speicher: ------------------");
    for(int i = 0; i < numberOfSensors; i ++) {
        Serial.print(i);
        Serial.print(":");
        Serial.print(EEPROM.read(i));
        Serial.println(" ");
    }
    readThresholdsFromROM();
    
    waitTillEnter();

}

/**
 * returns value of every sensor in terminal for testing reasons
 * 
 * Example output in consol:
 * .0X 1_ 2_ 3X 4X.
 * That means that sensors 0, 3 and 4 measure black
 * while 1 and 2 measure white
*/
void ausgabe()
{
    for (int i = 0; i < numberOfSensors; i++)
    {
        if (sensors[i] < 0 || threshold[i] <= 0)
        {
            Serial.print(" ");
            continue;
        }
        Serial.print(i);
        if (messwerte[i] == 1)
            Serial.print("X");
        else
            Serial.print("_");
    }
    Serial.println(". ");
}

/**
 * Halts programm untill enter-key is pressed
*/
void waitTillEnter()
{
    while (!Serial.available());
    Serial.readStringUntil('\n');
}

/**
 * Checks, if there is a double orthogonal line
 * thats important for special information about the road
 * 
 * @param left (L) and @param right (R) is either 0 or 1. For instance: L = 0 & R = 1 means: check if there is a double line right 
 * 
 * @return Has double orthogonal line been detected?
*/
bool checkPinsInRange(int left, int right){
    int numberOfWhite = 0;
    uint16_t pinOutput = getSensorData();
    pinOutput = ~pinOutput;
    for(int i = right * ((int)(numberOfSensors * 0.32)); i < (left ? ((int)(numberOfSensors*0.68)) : numberOfSensors); i++) {
        if(pinOutput & (1 << (i))) numberOfWhite++;
    }
    int threshold = 2;
    return ((numberOfWhite + threshold) >= (int)(numberOfSensors*0.6));
}

/**
 * returns bool:  Has double orthogonal line been detected on hole line?
 * 
 * @return Has double orthogonal line been detected on hole line?
*/
bool fullLine() {
    counterSinceLastOrthogonalLine++;
    if(checkPinsInRange(1,0) && checkPinsInRange(0,1)) {
        if(isIn(counterSinceLastOrthogonalLine,1,10) ) {
            counterSinceLastOrthogonalLine = -1;
            return true;
        }
        counterSinceLastOrthogonalLine = -1;
    }
    return false;
}


/**
 * returns bool:  Has double orthogonal line been detected on right side of line?
 * 
 * @return Has double orthogonal line been detected on right side of line?
*/
bool halfLineRight() {
    counterSinceLastOrthogonalLineRight++;
    if(checkPinsInRange(0,1) && !checkPinsInRange(1,0) ) {
        if(isIn(counterSinceLastOrthogonalLineRight,1,10) ) {
            counterSinceLastOrthogonalLineRight = -1;
            return true;
        }
        counterSinceLastOrthogonalLineRight = -1;
    }
    return false;
    
}


/**
 * returns bool:  Has double orthogonal line been detected on left side of line?
 * 
 * @return Has double orthogonal line been detected on left side of line?
*/
bool halfLineLeft() {
    counterSinceLastOrthogonalLineLeft++;
    if(checkPinsInRange(1,0) && !checkPinsInRange(0,1) ) {
        if(isIn(counterSinceLastOrthogonalLineLeft,1,10) ) {
            counterSinceLastOrthogonalLineLeft = -1;
            return true;
        }
        counterSinceLastOrthogonalLineLeft = -1;
    }
    return false;
}

/**
 * Answers question: is x between a and b?
 * 
 * @param x is number to check, @param a is left border, @param b is right border
 * 
 * @return is x between a and b?
*/
bool isIn(int x, int a, int b) {
    return a <= x && x <= b;
}

/**
 * Saves values from threshold[] array on permanent storage on ESP32
*/
void saveThresholdsToROM() {
    for(int i = 0; i < numberOfSensors; i++) {
        EEPROM.write(i, (threshold[i] / 10));
        EEPROM.commit();

    }
    Serial.println("\nDone with saving. Gespeicherte Werte:");
    for(int i = 0; i < numberOfSensors; i ++) {
        Serial.print(i);
        Serial.print(":");
        Serial.print(EEPROM.read(i));
        Serial.println(" ");
    }
}

/**
 * Loads values from permanent storage on ESP32 on threshold[] array
*/
void readThresholdsFromROM() {
    for(int i = 0; i < numberOfSensors; i++) {
        threshold[i] = EEPROM.read(i) * 10;
    }
}
