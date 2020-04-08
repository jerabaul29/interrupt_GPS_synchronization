import serial
from datetime import datetime

serial_port = "/dev/ttyACM0"
baudrate = 115200

class TrackSeconds(object):
    def __init__(self):
        self.current_second = datetime.now().second

    def start_second(self):
        measured_second = datetime.now().second
        if (measured_second != self.current_second):
            self.current_second = measured_second
            return True

        return False

string_read = ""

with serial.Serial(serial_port, baudrate, timeout=0) as ser:
    print("serial connected")

    second_tracker = TrackSeconds()

    while True:
        if (second_tracker.start_second()):
            print("start new second")
            print(datetime.now())

        if (ser.in_waiting > 0):
            crrt_char = ser.read().decode()

            if (crrt_char == '\n'):
                print(string_read)
                print(datetime.now())
                string_read = ""
            else:
                string_read += crrt_char

            