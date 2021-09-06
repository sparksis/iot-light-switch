#include "lib1.h"

#define USE_SERIAL Serial

const char LIGHT_ON_URI[] = "http://maker.ifttt.com/trigger/light_on/with/key/bpGQDLtVGRPza0T7xPXGaR";
const char LIGHT_OFF_URI[] = "http://maker.ifttt.com/trigger/light_off/with/key/bpGQDLtVGRPza0T7xPXGaR";


Light::Light() { }

void Light::turnOn() {
  get(LIGHT_ON_URI);
}
void Light::turnOff() {
  get(LIGHT_OFF_URI);
}

void Light::get(const char url[]) {
        USE_SERIAL.print("[HTTP] begin...\n");
        http.begin(url); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
}
