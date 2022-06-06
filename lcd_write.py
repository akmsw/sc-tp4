import RPi_I2C_driver as LCD
import sys

string = sys.argv[1]
mylcd = LCD.lcd()
mylcd.lcd_display_string(string,1)
