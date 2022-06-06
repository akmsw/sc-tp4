import RPi_I2C_driver as LCD
import sys

string = sys.argv[1]
mylcd = LCD.lcd()
mylcd.lcd_clear()
if(len(string)>16):
    string1 = string[:16]
    string2 = string[16:]
    mylcd.lcd_display_string(string1,1)
    mylcd.lcd_display_string(string2,2)
else:
    mylcd.lcd_display_string(string,1)

