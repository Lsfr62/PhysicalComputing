#include <Arduino.h>
//TODO Werte in Speicher speichern und kallibrierung skippen
const int numberOfSensors = 16;
int sensors[numberOfSensors];
//int steckplatzZuPinNummerRechts[19]; // z.B. der 5. Steckplatz auf dem Board ist Pin 2, also wäre steckplatzZuPinNummer[5] == 2
//int steckplatzZuPinNummerLinks[19]; 
int messwerte[numberOfSensors];
int threshold[numberOfSensors]; //jeder Sensr braucht einen individuellen Wert, um beste Ergebnisse zu bringen
int control = 13; // Ist der VCC Anschluss
void ausgabe();
void callibriereThreshold();
void waitTillEnter();
void sensorUpdate();
void sensorSetup();

/**
 * Ruft Daten von Sensoren ab
 * 
 * @return ganze Zahl der länge 16 zurück, worin 1 = schwarz, weiß = 0 ist
 * 
 * Beispielaufruf: 
 * Serial.println((int)getSensorData(), BIN);
 * 
 * Achtung: Gibt auch dann 0 zurück, wenn kein Sensor vorhanden
*/
uint16_t getSensorData() {
    sensorUpdate();
    int16_t erg = 0;
    for(int i = 0; i < numberOfSensors; i++) {
        if (sensors[i] < 0) continue;
        erg = erg + (messwerte[i] << i) ;
    }
    return erg;
}

/**
 * Sorgt dafür, dass die Messerte in messwerte[] auf dem neusten Stand sind.
*/
void sensorUpdate()
{
    for (int i = 0; i < numberOfSensors; i++)
    {
        if (threshold[i] < 0)
            continue;
        digitalWrite(control, HIGH);

        pinMode(sensors[i], OUTPUT);    //pinModeAll(OUTPUT);
        digitalWrite(sensors[i], HIGH); //digitalWrite(ioLine, HIGH);
        delayMicroseconds(15);
        pinMode(sensors[i], INPUT); //pinMode(ioLine, INPUT);

        delayMicroseconds(threshold[i]); //mehr 0-en => Zahl runter, mehr 1-er => Zahl hoch

        messwerte[i] = digitalRead(sensors[i]);
        digitalWrite(control, LOW);
        delayMicroseconds(500);
    }
    ausgabe();
    
}


void sensorSetup()
{
    for (int i = 0; i < numberOfSensors; i++)
    {
        sensors[i] = -1;
        messwerte[i] = -1;
        threshold[i] = -1;
    }

    /*
    sensors[1 - 1] = 5;
    //sensors[2 - 1] = 14;
    sensors[3 - 1] = 18; 
    //sensors[4 - 1] = 27;
    sensors[5 - 1] = 19;
    //sensors[6 - 1] = 26;
    sensors[7 - 1] = 21;
    //sensors[8 - 1] = 25;
    sensors[9 - 1] = 22;
    //sensors[10 - 1] = 33;
    sensors[11 - 1] = 9;
    //sensors[12 - 1] = 32;
    sensors[13 - 1] = 13;
    //sensors[14 - 1] = 8;
    sensors[15 - 1] = 12;
    //sensors[(16 - 1)] = 7;
    */
   sensors[1 - 1] = 27;
    //sensors[2 - 1] = 14;
    sensors[3 - 1] = 2; 
    //sensors[4 - 1] = 27;
    sensors[5 - 1] = 12;
    //sensors[6 - 1] = 26;
    sensors[7 - 1] = 18;
    //sensors[8 - 1] = 25;
    sensors[9 - 1] = 19;
    //sensors[10 - 1] = 33;
    sensors[11 - 1] = 26;
    //sensors[12 - 1] = 32;
    sensors[13 - 1] = 5;
    //sensors[14 - 1] = 8;
    //sensors[15 - 1] = 21;
    //sensors[(16 - 1)] = 7;
 /*
    steckplatzZuPinNummerLinks[2] = 11;
    steckplatzZuPinNummerLinks[1] = ;
    steckplatzZuPinNummerLinks[1] = ;
    steckplatzZuPinNummerLinks[1] = ;
    steckplatzZuPinNummerLinks[1] = ;
    steckplatzZuPinNummerLinks[1] = ;
    steckplatzZuPinNummerLinks[1] = ;
    steckplatzZuPinNummerLinks[1] = ;
    steckplatzZuPinNummerLinks[1] = ;
    steckplatzZuPinNummerLinks[1] = ;
    steckplatzZuPinNummerLinks[1] = ;
    steckplatzZuPinNummerLinks[1] = ;
    steckplatzZuPinNummerLinks[1] = ;
    steckplatzZuPinNummerLinks[1] = ;
    steckplatzZuPinNummerLinks[1] = ;
    steckplatzZuPinNummerLinks[1] = ;
    steckplatzZuPinNummerLinks[1] = ;
    steckplatzZuPinNummerLinks[1] = ;

    steckplatzZuPinNummerRechts[1] = ;
    steckplatzZuPinNummerRechts[1] = ;
    steckplatzZuPinNummerRechts[1] = ;
    steckplatzZuPinNummerRechts[1] = ;
    steckplatzZuPinNummerRechts[1] = ;
    steckplatzZuPinNummerRechts[1] = ;
    steckplatzZuPinNummerRechts[1] = ;
    steckplatzZuPinNummerRechts[1] = ;
    steckplatzZuPinNummerRechts[1] = ;
    steckplatzZuPinNummerRechts[1] = ;
    steckplatzZuPinNummerRechts[1] = ;
    steckplatzZuPinNummerRechts[1] = ;
    steckplatzZuPinNummerRechts[1] = ;
    steckplatzZuPinNummerRechts[1] = ;
    steckplatzZuPinNummerRechts[1] = ;
    steckplatzZuPinNummerRechts[1] = ;
    steckplatzZuPinNummerRechts[1] = ;
    steckplatzZuPinNummerRechts[1] = ;
    steckplatzZuPinNummerRechts[1] = ;
*/
    //zu viele 0-en => Zahl runter, zu viele  1-er => Zahl hoch

    //RC Kit Beschreibzung soll in Doc!
    //callibriereThreshold();
    threshold[0] = 1160;
    threshold[2] = 610;
    threshold[4] = 1030;
    threshold[6] = 1135;
    threshold[8] = 1010;
    threshold[10] = 1090;
    threshold[12] = 1030;
    
}


/**
 * Ermittelt Threshold-Werte für jeden Sensor bei Tastendruck.
 * 
 * Der Threshold ist eine Zahl, die für jeden Sensor einzelnt bestimmt werden muss.
 * Dafür werden für jeden Sensor einzelnt Werte ausprobiert. Dafür werden alle
 * Werte nacheinander durch gegangen. Zunächst wird ein oberer 
 * Grenzwert bestimmt (Supremum-Threshold), der eigentliche Threshold-Wert liegt gewiss darunter.
 * Dann wird ein unterer Grenzwet bestimmt (Infimum-Threshold), der eignetliche Threshold-Wert 
 * liegt gewiss darüber. Dann wird das arithmetische Mittel dieser Zahlen als 
 * Threshold gespeichert. Alle Daten werden in Arrays gespeichert;
 * infimumThresholds[3] entspricht der unteren Grenze für den Sensor 4 (4, da wir 3+1 rechnen müssen).
 * 
*/
void callibriereThreshold()
{


    int supremumThresholds[numberOfSensors];
    int infimumThresholds[numberOfSensors];
    for (int i = 0; i < numberOfSensors; i++)
    {
        supremumThresholds[i] = -1;
        infimumThresholds[i] = -1;
    }
    Serial.println("Halte Sensor auf schwartz und drücke Enter.");

    waitTillEnter();
    Serial.println("Kallibriere Schwartz...");
    for (int i = 0; i < numberOfSensors; i++)
    {
        if (sensors[i] < 0)
            continue;
        int steps = 10;
        int triggerLimit = 0;
        int testLimit = 4;
        for (int thresholdTry = 0; thresholdTry < 5000; thresholdTry = thresholdTry + steps)
        {
            digitalWrite(control, HIGH);

            pinMode(sensors[i], OUTPUT);    //pinModeAll(OUTPUT);
            digitalWrite(sensors[i], HIGH); //digitalWrite(ioLine, HIGH);
            delayMicroseconds(15);
            pinMode(sensors[i], INPUT);      //pinMode(ioLine, INPUT);
            delayMicroseconds(thresholdTry); //mehr 0-en => Zahl runter, mehr 1-er => Zahl hoch
            if (digitalRead(sensors[i]) == 0)
                triggerLimit++;

            if (digitalRead(sensors[i]) == 1)
                triggerLimit = 0;
            if (triggerLimit == testLimit)
            { // es soll drei mal hintereinander eine 0 gemessen worden sein
                supremumThresholds[i] = thresholdTry;
                break;
            }
            digitalWrite(control, LOW);
            delayMicroseconds(500);

            if (5000 - steps - steps / 2 < thresholdTry)
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
            digitalWrite(control, HIGH);

            pinMode(sensors[i], OUTPUT);    //pinModeAll(OUTPUT);
            digitalWrite(sensors[i], HIGH); //digitalWrite(ioLine, HIGH);
            delayMicroseconds(15);
            pinMode(sensors[i], INPUT);      //pinMode(ioLine, INPUT);
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
            digitalWrite(control, LOW);
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
    waitTillEnter();
    //while(true);
}

/**
 * Gibt jeden Senor in der Console aus zu Testzwecken
 * 
 * In der Konsole sieht man etwa folgendes:
 * .0X 1_ 2_ 3X 4X.
 * Das bedeutet, dass die Sensoren 0, 3 und 4 einen schwarzen Untergrund
 * erkennen, die Sensoren 1 und 2 einen weißen
*/
void ausgabe()
{
    for (int i = 0; i < numberOfSensors; i++)
    {
        if (sensors[i] < 0)
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
 * Hält das Programm so lange an, bis Enter gedrückt wird
*/
void waitTillEnter()
{
    while (!Serial.available());
    Serial.readStringUntil('\n');
}