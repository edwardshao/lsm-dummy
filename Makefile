
ifneq ($(KERNELRELEASE),)
obj-m	:= lsm_dummy.o
obj-m	:= lsm_dummy_patch_symbol.o
else
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif

install:
	sudo insmod lsm_dummy.ko

remove:
	sudo rmmod lsm_dummy

install_patched:
	sudo insmod lsm_dummy_patch_symbol.ko

remove_patched:
	sudo rmmod lsm_dummy_patch_symbol

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions modules.order Module.symvers

depend .depend dep:
	$(CC) $(EXTRA_CFLAGS) -M *.c > .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif
