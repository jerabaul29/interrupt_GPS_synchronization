#include <Arduino.h>
#include "time_catcher.h"

volatile bool TimeCatcher::to_read_flag = false;
volatile long TimeCatcher::measured_time = 0; 

TimeCatcher time_catcher;

void TimeCatcher::measure_time(){
    measured_time = micros();
    to_read_flag = true;
}

bool TimeCatcher::available_time(){
    return to_read_flag;
}

long TimeCatcher::get_time(void){
    if (!available_time()){
        // this is an error!
        return(0);
    }
    else{
        to_read_flag = false;
        return(measured_time);
    }
}

void ISR_measure_time(void){
    time_catcher.measure_time();
}

void TimeCatcher::turn_on(int pin, int mode, bool pullup){
    pin = pin;
    mode = mode;
    pullup = pullup;

    if (pullup){
        pinMode(pin, INPUT_PULLUP);
    }
    else{
        pinMode(pin, INPUT);
    }

    attachInterrupt(digitalPinToInterrupt(pin), ISR_measure_time, mode);
}

void TimeCatcher::turn_off(void){
    detachInterrupt(digitalPinToInterrupt(pin));
}