#include <Arduino.h>
#include "time_catcher.h"
#include <Adafruit_GPS.h>

/*
Boards used:
- Adafruit GPS breakout
- Arduino Mega

Wiring:
- Mega USB to computer
- Mega 5V to GPS Vin
- Mega GND to GPS GND
- Mega pin 2 (interrupt pin) to GPS PPS
- Mega pin 19 (RX1) to GPS TX
- Mega pin 18 (TX1) to GPS RX

Libraries:
- see the time_catcher.{h, cpp} in this folder
- see the Adafruit_GPS in ../lib

Note about PPS vs. GPS:
- see discussion here: https://electronics.stackexchange.com/questions/254216/gps-pps-signal-corresponds-to-data-time
- the GPS output for a given second probably comes AFTER the PPS rising edge
- ie it should be: time_at_rising_PPS = most_recent_gps_time_utc + 1 second
*/

constexpr unsigned long baud_rate = 115200;
constexpr uint8_t pin_interrupt = 2;
constexpr uint8_t pin_utc = 3;
constexpr bool pullup = false;

unsigned long delay_2_to_3 = 0;
unsigned long time_2;
unsigned long time_3;

TimedInterrupt crrt_timed_interrupt;

Adafruit_GPS GPS(&Serial1);

void setup() {
  Serial.begin(baud_rate);
  delay(10);
  Serial.println(F("booted..."));

  time_catcher.turn_on(pin_interrupt, RISING, pullup);
  time_catcher.turn_on(pin_utc, RISING, pullup);

  Serial.print(F("interrupt attached to pin "));
  Serial.println(pin_interrupt);

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
    crrt_timed_interrupt = time_catcher.get_measurement();

    Serial.print(F("interrupt pin "));
    Serial.print(mapping_index_to_interrupt_pin[crrt_timed_interrupt.interrupt_index]);
    Serial.print(F(" triggered "));
    Serial.print(crrt_timed_interrupt.micros);
    Serial.print(F(" elapsed "));
    Serial.println(crrt_timed_interrupt.elapsed);

    if (mapping_index_to_interrupt_pin[crrt_timed_interrupt.interrupt_index] == 2){
      time_2 = crrt_timed_interrupt.micros;
    }
    else if (mapping_index_to_interrupt_pin[crrt_timed_interrupt.interrupt_index] == 3){
      time_3 = crrt_timed_interrupt.micros;
      delay_2_to_3 = time_3 - time_2;
      Serial.print(F("delay 2 to 3 is "));
      Serial.println(delay_2_to_3);
    }
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