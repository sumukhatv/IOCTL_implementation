A simple implementation of IOCTL system call. 

Contains two parts:
	1. The kernel module which contains the IOCTL handler.
	2. The userland program that fires the IOCTL system call.

The ioctl_impl_drv.c is a simple device driver that implements the IOCTL handler. The ioctlHandler.h contains code releated to the handling of IOCTL system call.

The userland program <ioctl_impl_frontend.c> makes IOCTL call twice. Once for sending data from the userland to the kernel space and next time for receiving data from the kernel space.

The compile_and_load_drv.sh script will compile and load the device driver.

Usage:
	- Execute the compile_and_load_drv.sh to compile the device driver and load it.
	- Compile and execute the ioctl_impl_frontend.c
	- Execute the unload_drv.sh to unload the device driver.  