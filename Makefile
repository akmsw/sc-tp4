obj-m    := display_driver.o

KDIR    := /lib/modules/$(shell uname -r)/build
PWD    := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	gcc lcdwriter.c -o lcdwriter
	gcc lcd_interface.c -o interface
	sudo cp lcd_write.py /usr/bin/lcd_write.py
	sudo cp RPi_I2C_driver.py /usr/bin/RPi_I2C_driver.py
	sudo cp lcdwriter /usr/bin/lcdwriter
	sudo insmod display_driver.ko

clean:
	sudo rmmod display_driver.ko
	sudo rm /usr/bin/lcd_write.py /usr/bin/RPi_I2C_driver.py /usr/bin/lcdwriter
	sudo rm display_driver.ko
