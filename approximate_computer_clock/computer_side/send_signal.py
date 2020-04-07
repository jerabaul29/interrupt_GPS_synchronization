import serial
from datetime import datetime

serial_port = "/dev/ttyACM1"
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

with serial.Serial(serial_port, baudrate, timeout=0) as ser:
    print("serial connected")

    second_tracker = TrackSeconds()

    while True:
        if (second_tracker.start_second()):
            print("start new second")
            ser.write(b'C')
            ser.flush()

        if (ser.in_waiting > 0):
            print(ser.read())