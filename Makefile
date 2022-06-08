obj-m    := display_kernel.o

KDIR    := /lib/modules/$(shell uname -r)/build
PWD    := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	mkdir -p ~/lcd
	gcc lcdwriter.c -o lcdwriter
	gcc lcd_interface.c -o interface
	gcc dht11reader.c -o dht11reader
	sudo cp lcd_write.py /usr/bin/lcd_write.py
	sudo cp RPi_I2C_driver.py /usr/bin/RPi_I2C_driver.py
	sudo cp lcdwriter /usr/bin/lcdwriter
	sudo insmod display_kernel.ko

clean:
	sudo rmmod display_kernel.ko
	sudo rm /usr/bin/lcd_write.py /usr/bin/RPi_I2C_driver.py /usr/bin/lcdwriter
	sudo rm display_kernel.ko
