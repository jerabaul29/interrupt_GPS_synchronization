#include <Arduino.h>
#include "time_catcher.h"

volatile bool TimeCatcher::to_read_flag = false;
volatile long TimeCatcher::measured_time = 0; 
int TimeCatcher::pin = 0;  // dummy value

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

void TimeCatcher::turn_on(int pin){
    pin = pin;
    attachInterrupt(digitalPinToInterrupt(pin), ISR_measure_time, RISING);
}

void TimeCatcher::turn_off(void){
    detachInterrupt(digitalPinToInterrupt(pin));
}