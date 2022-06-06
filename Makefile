obj-m    := display_kernel.o

KDIR    := /lib/modules/$(shell uname -r)/build
PWD    := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	mkdir -p ~/lcd
	cp lcd_write.py ~/lcd/lcd_write.py
	sudo insmod display_kernel.ko

clean:
	sudo rmmod display_kernel.ko
	sudo rm -rf ~/lcd
	sudo rm display_kernel.ko
	