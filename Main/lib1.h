#include <HTTPClient.h>


class Light {
public: 
    Light();
    void turnOn();
    void turnOff();

private: 
  void get(const char url[]);
  HTTPClient http;

};
