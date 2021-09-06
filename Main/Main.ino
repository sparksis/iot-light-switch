#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include "lib1.h"

// this constant won't change:
const int  buttonPin = 33;    // the pin that the pushbutton is attached to

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

WiFiMulti wifiMulti;
Light light;

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize serial communication:
  Serial.begin(115200);
  for(uint8_t t = 4; t > 0; t--) {
      Serial.printf("[SETUP] WAIT %d...\n", t);
      Serial.flush();
      delay(1000);
  }

    wifiMulti.addAP("HiddenLeafNetwork 2.4GHz", "password");
}


void loop() {
  if((wifiMulti.run() == WL_CONNECTED)) {
    // read the pushbutton input pin:
    buttonState = digitalRead(buttonPin);

    // compare the buttonState to its previous state
    if (buttonState != lastButtonState) {
      // if the state has changed, increment the counter
      if (buttonState == HIGH) {
        // if the current state is HIGH then the button went from off to on:
        buttonPushCounter++;
        Serial.println("on");
        Serial.print("number of button pushes: ");
        Serial.println(buttonPushCounter);
        light.turnOn();
      } else {
        // if the current state is LOW then the button went from on to off:
        Serial.println("off");
        light.turnOff();
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state, for next time through the loop
    lastButtonState = buttonState;
  } else {
    Serial.printf("[%d] Wifi not connected!\n", buttonPushCounter);
    delay(5000);
  }
}
