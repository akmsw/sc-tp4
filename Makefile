obj-m    := display_kernel.o

KDIR    := /lib/modules/$(shell uname -r)/build
PWD    := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	mkdir -p ~/lcd
	gcc python_executer.c -o lcdwriter
	cp lcd_write.py /usr/bin/lcd_write.py
	cp RPi_I2C_driver.py /usr/bin/RPi_I2C_driver.py
	cp lcdwriter /usr/bin/lcdwriter
	sudo insmod display_kernel.ko

clean:
	sudo rmmod display_kernel.ko
	sudo rm -rf ~/lcd
	sudo rm display_kernel.ko
