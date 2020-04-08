#include <Arduino.h>
#include "time_catcher.h"

volatile uint8_t TimeCatcher::to_read_flag_array = 0;
volatile unsigned long TimeCatcher::measured_time[] = {0, 0, 0, 0, 0, 0}; 
volatile unsigned long TimeCatcher::elapsed_time[] = {0, 0, 0, 0, 0, 0}; 

TimeCatcher time_catcher;

void TimeCatcher::measure_time(uint8_t interrupt_index){
    unsigned long crrt_micros = micros();
    elapsed_time[interrupt_index] = crrt_micros - measured_time[interrupt_index];
    measured_time[interrupt_index] = crrt_micros;
    to_read_flag_array |= (0b1 << interrupt_index);
}

bool TimeCatcher::available_time(){
    return (!to_read_flag_array == 0);
}

TimedInterrupt TimeCatcher::get_measurement(void){
    // debug
    // Serial.println(F("to_read_flag_array"));
    // for (int i=0; i<number_of_interrupt_capable_pins; i++){
    //     Serial.print((to_read_flag_array>>i) & (0b00000001));
    //     Serial.println();
    // }
    // Serial.println(F("measured_time"));
    // for (int i=0; i<number_of_interrupt_capable_pins; i++){
    //     Serial.print(measured_time[i]);
    //     Serial.println();
    // }

    if (!available_time()){
        // this is an error!
        return(TimedInterrupt{255, 0, 0});
    }
    else{
        // use bitmask to find the first active measurement coming
        uint8_t crrt_mask = (0b1);
        uint8_t interrupt_index;
        for (interrupt_index=0; interrupt_index<number_of_interrupt_capable_pins; interrupt_index++){
            if (crrt_mask & to_read_flag_array){
                break;
            }
            crrt_mask <<= 1;
        }

        to_read_flag_array ^= crrt_mask;
        TimedInterrupt result {interrupt_index, measured_time[interrupt_index], elapsed_time[interrupt_index]};
        return(result);
    }
}

//---------------------------------------- 
// The ISR routines. TODO: find a better way to generate. Use macro? Some form of templating?
void ISR_measure_time_0(void){
    time_catcher.measure_time(0);
}

void ISR_measure_time_1(void){
    time_catcher.measure_time(1);
}

void ISR_measure_time_2(void){
    time_catcher.measure_time(2);
}

void ISR_measure_time_3(void){
    time_catcher.measure_time(3);
}

void ISR_measure_time_4(void){
    time_catcher.measure_time(4);
}

void ISR_measure_time_5(void){
    time_catcher.measure_time(5);
}
//---------------------------------------- 

void TimeCatcher::turn_on(uint8_t pin, int mode, bool pullup){
    if (pullup){
        pinMode(pin, INPUT_PULLUP);
    }
    else{
        pinMode(pin, INPUT);
    }

    if (mapping_interrupt_pin_to_index[pin] == 255){
        // ERROR!
    }

    if (mapping_interrupt_pin_to_index[pin] == 0){
        attachInterrupt(digitalPinToInterrupt(pin), ISR_measure_time_0, mode);
    }
    if (mapping_interrupt_pin_to_index[pin] == 1){
        attachInterrupt(digitalPinToInterrupt(pin), ISR_measure_time_1, mode);
    }
    if (mapping_interrupt_pin_to_index[pin] == 2){
        attachInterrupt(digitalPinToInterrupt(pin), ISR_measure_time_2, mode);
    }
    if (mapping_interrupt_pin_to_index[pin] == 3){
        attachInterrupt(digitalPinToInterrupt(pin), ISR_measure_time_3, mode);
    }
    if (mapping_interrupt_pin_to_index[pin] == 4){
        attachInterrupt(digitalPinToInterrupt(pin), ISR_measure_time_4, mode);
    }
    if (mapping_interrupt_pin_to_index[pin] == 5){
        attachInterrupt(digitalPinToInterrupt(pin), ISR_measure_time_5, mode);
    }
}

void TimeCatcher::turn_off(uint8_t pin){
    detachInterrupt(digitalPinToInterrupt(pin));
}