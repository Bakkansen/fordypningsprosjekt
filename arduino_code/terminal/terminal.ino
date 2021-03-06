/*
 */

#include <SoftwareSerial.h>
#include <PLabBTSerial.h>

#define txPin 10  // Tx pin on Bluetooth unit
#define rxPin 11  // Rx pin on Bluetooth unit


PLabBTSerial btSerial(txPin, rxPin);

void setup()
{
    Serial.begin(9600);   // Open serial communication to Serial Monitor
    btSerial.begin(9600); // Open serial communication to Bluetooth unit
}

void loop() {
    while (btSerial.available()) { // If input available from Bluetooth unit
      char c = btSerial.read();    // Read character from from Bluetooth unit
      Serial.write(c);             // Write that character to Serial Monitor
    };
    while (Serial.available()) { // If input available from Serial Monitor
      char c = Serial.read();    // Read character from from Serial Monitor
      btSerial.write(c);         // Write that character to Bluetooth unit
    };
}

