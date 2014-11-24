#include <sys/modctl.h>
#include <sys/cmn_err.h>
#include <sys/ddi.h>
#include <sys/sunddi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/errno.h>
#include <sys/open.h>
#include <sys/cred.h>
#include <sys/uio.h>
#include <sys/devops.h>
#include <sys/conf.h>

#include "ioctlHandler.h" // contains the ioctl entry point


static int __attach(dev_info_t *dip, ddi_attach_cmd_t cmd);
static int __detach(dev_info_t *dip, ddi_detach_cmd_t cmd);
static int __getinfo(dev_info_t *dip, ddi_info_cmd_t cmd, void *arg, void **resultp);
static int __prop_op(dev_t dev, dev_info_t *dip, ddi_prop_op_t prop_op, int flags, char *name, caddr_t valuep, int *lengthp);
static int __write(dev_t dev, struct uio *uiop, cred_t * credp);
static int __read(dev_t dev, struct uio *uiop, cred_t *  credp);
static int __close(dev_t dev, int flag, int otyp,        cred_t *cred); 
static int __open(dev_t *devp, int flag, int otyp,       cred_t *cred);
static int ioctlHandler(dev_t dev, int cmd, intptr_t arg, int mode, cred_t *credp, int *rvalp);


static struct cb_ops __cb_ops = {
    __open,
    __close,
    nodev,
    nodev,
    nodev,
    nodev,
    nodev,
    ioctlHandler, // ioctl entry point
    nodev,
    nodev,
    nodev,
    nochpoll,
    __prop_op,
    NULL,
    D_NEW | D_MP,
    CB_REV,
    nodev,
    nodev
};

static struct dev_ops __dev_ops = {
    DEVO_REV,
    0,
    __getinfo,
    nulldev,
    nulldev,
    __attach,
    __detach,
    nodev,
    &__cb_ops,
    (struct bus_ops *)NULL,
    nodev,
    ddi_quiesce_not_needed 
};

static struct modldrv md = {
    &mod_driverops,
    "IOCTL implementation",
    &__dev_ops
};

static struct modlinkage ml = {
    MODREV_1,
    &md,
    NULL
};

dev_info_t *__dip;

int _init(void) {
    //cmn_err(CE_NOTE, "Inside _init");
	return(mod_install(&ml));
}

int _info(struct modinfo *modinfop) {
    //cmn_err(CE_NOTE, "Inside _info");
    return(mod_info(&ml, modinfop)); 
}

int _fini(void) {
    //cmn_err(CE_NOTE, "Inside _fini");
	return(mod_remove(&ml));
}

static int __attach(dev_info_t *dip, ddi_attach_cmd_t cmd) {
    //cmn_err(CE_NOTE, "Inside __attach");
    switch(cmd) {
        case DDI_ATTACH:		
            __dip = dip;
            if(ddi_create_minor_node(dip, "0", S_IFCHR, ddi_get_instance(dip), DDI_PSEUDO, 0)!= DDI_SUCCESS) {
                cmn_err(CE_NOTE, "%s%d: attach: could not add character node. ", "_", 0);
                return(DDI_FAILURE);
            }
            else {
                cmn_err(CE_NOTE, "******************** Attach Accomplished!!!! ***************");
                return (DDI_SUCCESS);
            }
        default:
            return DDI_FAILURE;
    }
}

static int __detach(dev_info_t *dip, ddi_detach_cmd_t cmd) {
    //cmn_err(CE_NOTE, "Inside __detach");
    switch(cmd) {
        case DDI_DETACH:
            __dip=0;
            ddi_remove_minor_node(dip, NULL);
            cmn_err(CE_NOTE, "******************** Detach successful!!!! ***************");
            return DDI_SUCCESS;
        default:
            return DDI_FAILURE;
    }
}

static int __open(dev_t *devp, int flag, int otyp, cred_t *cred) {
    cmn_err(CE_NOTE, "Inside __open");
    return DDI_SUCCESS;
}

static int __close(dev_t dev, int flag, int otyp, cred_t *cred) {
    cmn_err(CE_NOTE, "Inside __close");
    return DDI_SUCCESS;
}

static int __prop_op(dev_t dev, dev_info_t *dip, ddi_prop_op_t prop_op, int flags, char *name, caddr_t valuep, int *lengthp) {
    //cmn_err(CE_NOTE, "Inside __prop_op");
    return(ddi_prop_op(dev, dip, prop_op, flags, name, valuep, lengthp));
}

static int __getinfo(dev_info_t *dip, ddi_info_cmd_t cmd, void *arg, void **resultp) {
    //cmn_err(CE_NOTE, "Inside __getinfo");
    switch(cmd) {
        case DDI_INFO_DEVT2DEVINFO:
            *resultp = __dip;
            return DDI_SUCCESS;
        case DDI_INFO_DEVT2INSTANCE:
            *resultp = 0;
            return DDI_SUCCESS;
        default:
            return DDI_FAILURE;
    }
}

