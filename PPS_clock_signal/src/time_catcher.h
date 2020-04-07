#ifndef TIME_CATCHER_H
#define TIME_CATCHER_H

/*
TimeCatcher - a simple class to catch the time when an interrupt is raised.

This class is specifically thought for the Arduino Mega. It allows to track
the time of interrupt on several distinct pins. Of course only interrupt-capable
pins can be used.
*/

// Mega, Mega2560, MegaADK:
// interrupt-capable pins:
// 2, 3, 18, 19, 20, 21
// corresponding to the indexes in arrays:
// 0, 1, 2,  3,  4,  5

constexpr uint8_t number_of_interrupt_capable_pins = 6;
constexpr uint8_t mapping_index_to_interrupt_pin[] {2, 3, 18, 19, 20, 21};
constexpr uint8_t mapping_interrupt_pin_to_index[] {255, 255,   0,   1, 255, 255, 255, 255, 255, 255,
                                                    255, 255, 255, 255, 255, 255, 255, 255,   2,   3,
                                                      4,   5};

struct TimedInterrupt{
    uint8_t interrupt_number;
    unsigned long micros;
};

class TimeCatcher{
    private:
        static volatile long measured_time[number_of_interrupt_capable_pins];
        static volatile uint8_t to_read_flag_array;  // each bit is a bool for 'this pin number should be read'

    public:
        static void measure_time(uint8_t pin_index);
        static bool available_time(void);
        static TimedInterrupt get_measurement(void);
        static void turn_on(uint8_t pin, int mode, bool pullup=true);
        static void turn_off(uint8_t pin);
};

extern TimeCatcher time_catcher;

#endif // !TIME_CATCHER