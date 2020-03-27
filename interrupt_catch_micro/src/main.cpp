/*
A simple sketch to illustrate the use of the TimeCatcher class

Setup:
  - get an Arduino Uno (tested on Uno, should be compatible with many other boards)
  - compile and upload the sketch
  - connect a wire to pin 2
  - each time the other end of the wire is put in contact to GND, a FALLING edge interrupt
      is triggered. It will be captured by the TimeCatcher, and information will be
      spit out on Serial at baudrate 115200.
    
  - NOTE 1: there is no min time between interrupts. If you touch / untouch the GND very
      quickly you will trigger many interrupts in short time (and spit out a lot through
      serial). This is a feature not a bug. If you want me to implement a min time before
      re-arming let me know, or simply put a time delay check after the get_time call.
  - NOTE 2: you have freedom over what kind of interrupt is caught. See the turn_on call.
*/

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