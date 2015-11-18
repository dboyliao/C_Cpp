obj-m:=chardev.o
KDIR:=/lib/modules/$(shell uname -r)/build
SRCPWD:=$(shell pwd)
all:
	make -C $(KDIR) M=$(SRCPWD) modules
clean:
	rm -rf chardev.o
