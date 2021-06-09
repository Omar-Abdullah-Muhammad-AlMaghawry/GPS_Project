#!/usr/bin/env python

"""serail_listener.py: Reads lines from serail bus
    and prints to command window
    or writes it into a file
."""

__author__ = "Ahmad Hassan Yassin"

import serial
from serial.tools import list_ports


print("############################")
print("Welcome to Genric Serial Listner")
print("This Program lists all available serail ports then listens to the selected prot at the selected rate")
print("Once you type the port's name CORRECTLY and baud rate the serIal input form the usb port will be printed to the screen as well as written in the file named \"serial_output.txt\"")
print("This Program assumes good intentioned usage please be mindful of your actions during usage")
print("")
print("List of available ports")
for i in list_ports.comports():
    print(i)
print("############################")
print("")
dev_name = input("Please type the port's name\n")
baud_rate = input("Please type the baud rate\n")
while(1):
    try :
        ser = serial.Serial(dev_name, baud_rate)
        file_out = open("serial_output.txt", "w")
        while(1):
            data = ser.readline()
            data = str(data)
            data = data[2:len(data)-5]
            print(data)
            file_out.write(str(data)+"\n")


    except NameError:
        print("Port Not Found or An Error has occured")
        print(NameError)




