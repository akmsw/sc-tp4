from time import sleep
import RPi.GPIO as GPIO
import dht11

# initialize GPIO
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.cleanup()

#open de display driver
f = open('/dev/display_driver','w')
# read data using pin 16
instance = dht11.DHT11(pin = 16)

while(-1):
    result = instance.read()
    if result.is_valid():
        s = "Temperature: %dC Humidity: %d%%" % (result.temperature,result.humidity)
        print(s)
        print(s,file=f,flush=True)
    else:
        print('ERROR',file=f,flush=True)
    sleep(1)