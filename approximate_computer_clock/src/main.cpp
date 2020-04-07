#include <Arduino.h>

/*
Get a 'C' clock signal byte from the computer at the start of each second and
relay it on digital pin 7
*/

constexpr uint8_t pin_start_second = 7;
char received;

void setup() {
  Serial.begin(115200);
  pinMode(pin_start_second, OUTPUT);

  while (Serial.available() > 0){
    Serial.read();
  }
}

void loop() {

  if (Serial.available() > 0){
    // pull UP
    digitalWrite(pin_start_second, HIGH);
    // read
    Serial.read();
    // send a small msg
    Serial.println(F("OK"));
    // pull down
    delay(1);
    digitalWrite(pin_start_second, LOW);
  }

}