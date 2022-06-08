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
while(-1):
    if result.is_valid():
        f.write("Temperature: %-3.1f C Humidity: %-3.1f %%" %(result.temperature,result.humidity))
    else:
        f.write("Error: %d" % result.error_code)
