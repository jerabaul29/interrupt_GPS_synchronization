#include <Arduino.h>
#include "time_catcher.h"

constexpr unsigned long baud_rate = 115200;
constexpr int pin_interrupt = 2;
constexpr bool pullup = true;

void setup() {
  Serial.begin(baud_rate);
  delay(10);
  Serial.println(F("booted..."));

  time_catcher.turn_on(pin_interrupt, FALLING, pullup);

  Serial.print(F("interrupt attached to pin "));
  Serial.println(pin_interrupt);
  Serial.println();
}

void loop() {
  if (time_catcher.available_time()){
    long time_recorded = time_catcher.get_time();

    Serial.print(F("interrupt was triggered at time "));
    Serial.println(time_recorded);
  }
}