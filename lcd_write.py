import RPi_I2C_driver as LCD
import sys

# string a mostrar por display lcd 16x2 via i2c
string = sys.argv[1]

mylcd = LCD.lcd()
mylcd.lcd_clear()

# si el string tiene más de 16 caracteres,
# mostramos los primeros 16 en la primera línea
# y los restantes en la segunda línea
if(len(string) > 16):
    string1 = string[:16]
    string2 = string[16:]
    mylcd.lcd_display_string(string1, 1)
    mylcd.lcd_display_string(string2, 2)
else:
    mylcd.lcd_display_string(string, 1)