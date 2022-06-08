import RPi.GPIO as GPIO
import dht11

# initialize GPIO
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.cleanup()

#open de display driver
f = open('/dev/display_driver','w')

# read data using pin 16
instance = dht11.DHT11(pin = 16)
result = instance.read()
print(result)
while(-1):
    if result.is_valid():
        f.write('Temperature: {} C Humidity: {}'.format(result.temperature,result.humidity))
    else:
        f.write('Error: {}'.format(result.error_code))
