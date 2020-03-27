#include <Arduino.h>
#include "time_catcher.h"

constexpr unsigned long baud_rate = 115200;
constexpr int pin_interrupt = 2;

void setup() {
  Serial.begin(baud_rate);
  Serial.println(F("booted..."));
  delay(10);

  time_catcher.turn_on(pin_interrupt);
  Serial.print(F("interrupt attached to pin "));
  Serial.println(pin_interrupt);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (time_catcher.available_time()){
    long time_recorded = time_catcher.get_time();

    Serial.print(F("interrupt was triggered at time "));
    Serial.println(time_recorded);
  }
}


