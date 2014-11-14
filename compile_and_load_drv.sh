/opt/solarisstudio12.3/prod/bin/cc -D_KERNEL -m64 -xarch=sse2a -xmodel=kernel -c ioctl_impl_drv.c

ld -r -o ioctl_impl_drv ioctl_impl_drv.o

cp ioctl_impl_drv.conf /usr/kernel/drv

cp ioctl_impl_drv /tmp

ln -s /tmp/ioctl_impl_drv /usr/kernel/drv/amd64/ioctl_impl_drv

cp ioctl_impl_drv /usr/kernel/drv/amd64/ioctl_impl_drv

add_drv ioctl_impl_drv
