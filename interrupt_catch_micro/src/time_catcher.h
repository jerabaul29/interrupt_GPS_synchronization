#ifndef TIME_CATCHER_H
#define TIME_CATCHER_H

/*
TimeCatcher - a simple class to catch the time when an interrupt is raised

Each time a given interrupt is raised, measure the current time as of micro()
and set a flag letting know that the time measurement is available.

use:
    - turn_on: to set up and start the catching
    - available_time: to check if an interrupt has been caught
    - get_time: to get the time that was caught
    - turn_off: to release the interrupt pin when done
*/
class TimeCatcher{
    private:
        static volatile long measured_time;
        static volatile bool to_read_flag;
        static int pin;
        static int mode;
        static bool pullup;

    public:
        static void measure_time(void);
        static bool available_time(void);
        static long get_time(void);
        static void turn_on(int pin, int mode, bool pullup=true);
        static void turn_off(void);
};

extern TimeCatcher time_catcher;

#endif // !TIME_CATCHER
