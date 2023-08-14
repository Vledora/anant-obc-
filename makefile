ifeq ($(KERNELRELEASE))
	KERNEL_SOURCE:= /lib/modules/$(uname -r)
	PWD:=$(shell pwd)

default:
	make -C /lib/modules/$(uname -r)/build M=$PWD modules

clean:
	make -C /lib/modules/$(uname -r)/build M=$PWD clean

else
	obj-m:=char_driver.o
endif