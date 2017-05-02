#include "PLab_PushButton.h";
#include <SoftwareSerial.h>

const int redButtonPin = 4;
const int greenButtonPin = 5;
const int yellowButtonPin = 6;

int redLedOn = 0;
int greenLedOn = 0;
int yellowLedOn = 0;

const int redLedPin = 7;
const int greenLedPin = 8;
const int yellowLedPin = 9;

PLab_PushButton redButton(redButtonPin);
PLab_PushButton greenButton(greenButtonPin);
PLab_PushButton yellowButton(yellowButtonPin);

const int rxPin = 10;
const int txPin = 11;

SoftwareSerial softSerial = SoftwareSerial(rxPin, txPin);

String receivedString = "";

void setup() {
  // put your setup code here, to run once:
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  softSerial.begin(9600);  
  Serial.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly:
  redButton.update();
  greenButton.update();
  yellowButton.update();

  if (redButton.pressed()) {
    Serial.println("Sent red");
    softSerial.write("#redButtonPressed");
    toggleLed("red");
  }
  if (greenButton.pressed()) {
    Serial.println("Sent green");
    softSerial.write("#greenButtonPressed");
    toggleLed("green");
  }
  if (yellowButton.pressed()) {
    Serial.println("Sent yellow");
    softSerial.write("#yellowButtonPressed");
    toggleLed("yellow");
  }
  
  while (softSerial.available() > 0) {
    char ch = softSerial.read();
    if (ch == 'X') {
      handleReceivedData(receivedString);
      receivedString = "";
    } else {
      receivedString += ch;
    }
  }  
}

void handleReceivedData(String data) {
  Serial.println(data);
  if (data == "#redButtonPressed") {
    toggleLed("red");
  }
  if (data == "#greenButtonPressed") {
    toggleLed("green");
  }
  if (data == "#yellowButtonPressed") {
    toggleLed("yellow");
  }
}

void toggleLed(String color) {
  if (color == "red") {
    redLedOn = !redLedOn;
    digitalWrite(redLedPin, redLedOn);
  }  
  if (color == "green") {
    greenLedOn = !greenLedOn;
    digitalWrite(greenLedPin, greenLedOn);
  }  
  if (color == "yellow") {
    yellowLedOn = !yellowLedOn;
    digitalWrite(yellowLedPin, yellowLedOn);
  }
}

