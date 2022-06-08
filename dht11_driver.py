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
result = instance.read()
while(-1):
    if result.is_valid():
        s = 'Temperature: {} C Humidity: {}'.format(result.temperature,result.humidity)
        print(s)
        f.write(s)
        f.flush()
    else:
        f.write("ERROR")
        f.flush()
    sleep(1)