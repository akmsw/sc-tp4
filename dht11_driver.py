from time import sleep

import RPi.GPIO as GPIO
import dht11
import os

# inicialización gpio
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.cleanup()

# apertura de driver de display
if os.path.exists('/dev/display_driver'):
    f = open('/dev/display_driver','w')
else:
    print('MÓDULO NO CARGADO')
    exit()

# vamos a leer por puerto 16
instance = dht11.DHT11(pin=16)

# bucle de lecturas mostradas por display
while(-1):
    result = instance.read()

    if result.is_valid():
        s = "Temperature: %dCHumidity: %d%%" % (result.temperature, result.humidity)
        print(s, file=f, flush=True)
    else:
        print('ERROR', file=f, flush=True)

    sleep(1)
