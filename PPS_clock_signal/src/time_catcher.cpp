#include <Arduino.h>
#include "time_catcher.h"

volatile uint8_t TimeCatcher::to_read_flag_array = 0;
volatile long TimeCatcher::measured_time[] = {0, 0, 0, 0, 0, 0}; 

TimeCatcher time_catcher;



void TimeCatcher::measure_time(uint8_t interrupt_nbr){
    measured_time[pin_nbr] = micros();
    to_read_flag_array |= (0b1 << pin_nbr);
}

bool TimeCatcher::available_time(){
    return (!to_read_flag_array == 0);
}

TimedInterrupt TimeCatcher::get_measurement(void){
    if (!available_time()){
        // this is an error!
        return(TimedInterrupt{255, 0});
    }
    else{
        // find which interrupt number
        int nbr_of_shifts = 0;

        while (true){

        }
    }
}

void ISR_measure_time(void){
    time_catcher.measure_time();
}

void TimeCatcher::turn_on(uint8_t pin, int mode, bool pullup){
    if (pullup){
        pinMode(pin, INPUT_PULLUP);
    }
    else{
        pinMode(pin, INPUT);
    }

    attachInterrupt(digitalPinToInterrupt(pin), ISR_measure_time, mode);
}

void TimeCatcher::turn_off(uint8_t pin){
    detachInterrupt(digitalPinToInterrupt(pin));
}