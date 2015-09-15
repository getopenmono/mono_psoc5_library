import serial;

port = serial.Serial("/dev/cu.usbmodem14141")
port.setDTR(True)
port.setDTR(False)