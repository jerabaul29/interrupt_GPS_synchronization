#include <Arduino.h>
#include "time_catcher.h"
#include <Adafruit_GPS.h>

constexpr unsigned long baud_rate = 115200;
constexpr int pin_interrupt = 2;
constexpr bool pullup = false;

unsigned long time_recorded = 0;
unsigned long previous_time_recorded = 0;
unsigned long time_elapsed_micro_s = 0;

Adafruit_GPS GPS(&Serial1);

void setup() {
  Serial.begin(baud_rate);
  delay(10);
  Serial.println(F("booted..."));

  time_catcher.turn_on(pin_interrupt, RISING, pullup);

  Serial.print(F("interrupt attached to pin "));
  Serial.println(pin_interrupt);
  Serial.println();

  Serial.print(F("start GPS..."));
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);

  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  GPS.sendCommand(PMTK_API_SET_FIX_CTL_1HZ);
  Serial.println(F("GPS started"));
}

void loop() {
  if (time_catcher.available_time()){
    time_recorded = time_catcher.get_time();
    time_elapsed_micro_s = time_recorded - previous_time_recorded;
    previous_time_recorded = time_recorded;

    Serial.print(F("interrupt was triggered at time "));
    Serial.println(time_recorded);
    Serial.print(F("time elapsed since last trigger (micro s): "));
    Serial.println(time_elapsed_micro_s);
  }

  char c_GPS = GPS.read();
  if (c_GPS)
  {
    Serial.print(c_GPS);

    if (c_GPS == '\n'){
      Serial.print(F("micros = "));
      Serial.println(micros());
    }
  }
}