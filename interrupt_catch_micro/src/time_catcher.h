#ifndef TIME_CATCHER_H
#define TIME_CATCHER_H

class TimeCatcher{
    // private:
    public:
        static volatile long measured_time;
        static volatile bool to_read_flag;
        static int pin;

    // public:
        static void measure_time(void);
        static bool available_time(void);
        static long get_time(void);
        static void turn_on(int pin);
        static void turn_off(void);
};

extern TimeCatcher time_catcher;

#endif // !TIME_CATCHER
