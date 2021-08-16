#include <Arduino.h>
//TODO Werte in Speicher speichern und kallibrierung skippen
const int numberOfSensors = 15;
int sensors[numberOfSensors];
int messwerte[numberOfSensors];
int threshold[numberOfSensors]; //jeder Sensr braucht einen individuellen Wert, um beste Ergebnisse zu bringen
//int messwert = 0;
//int ioLine = 15;
int control = 13;
int calibrationButton = 14;
void ausgabe();
void callibriereThreshold();
void waitTillEnter();
void sensorUpdate();

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
        if (sensors[i] < 0)
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
    //ausgabe();
    
}


void sensorSetup()
{
    for (int i = 0; i < numberOfSensors; i++)
    {
        sensors[i] = -1;
        messwerte[i] = -1;
        threshold[i] = -1;
    }
    sensors[1 - 1] = 15;
    sensors[3 - 1] = 27; //2;
    sensors[5 - 1] = 12;
    sensors[7 - 1] = 4;
    sensors[9 - 1] = 16;
    sensors[11 - 1] = 17;
    sensors[13 - 1] = 5;
    sensors[15 - 1] = 18;

    //zu viele 0-en => Zahl runter, zu viele  1-er => Zahl hoch

    //RC Kit Beschreibzung soll in Doc!
    callibriereThreshold();
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

    pinMode(calibrationButton, INPUT);

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