/*
This is the ioctl function handler.
It copies the 'arg' parameter sent from the userland to a buffer(drv_buf) int the kernel space and then copies data from the kernel space to the 'arg' and sends it to the userland.

Both ddi_copyin and ddi_copyout implementation is shown here.
*/

struct drv_buf {
        int key;
        int value;
};



static int ioctlHandler(dev_t dev, int cmd, intptr_t arg, int mode, cred_t *credp, int *rvalp) {
        struct drv_buf db1, db2;
        db2.key=22;
        db2.value=33;
        switch (cmd) {
        case 0:
            cmn_err(CE_NOTE, "Case 1 executed");
            if (ddi_copyout(&db2, arg, sizeof (struct drv_buf), mode) != 0) {
                cmn_err(CE_NOTE, "-----------------------COPY-OUT FAILED!!-----------------");
                //return (EFAULT);
            }
            break;
        case 1:
            cmn_err(CE_NOTE, "Case 2 executed");
            if (ddi_copyin(arg, &db1, sizeof(struct drv_buf), mode) != 0) {
                cmn_err(CE_NOTE, "-----------------------COPY-IN FAILED!!-----------------");
                //return(EFAULT);
            }
            cmn_err(CE_NOTE, "The value of d1.key = %d\n", db1.key);
            cmn_err(CE_NOTE, "The value of d1.value = %d\n", db1.value);
            break;
        default:
            cmn_err(CE_NOTE, "Default case executed");
            //generic "ioctl unknown" error
            return (ENOTTY);
    }
    return (0);
}

