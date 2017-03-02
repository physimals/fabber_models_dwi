/* dwi_models.cc Models for diffusion-weighted imaging

 Michael Chappell - IBME & FMRIB Analysis Group

 Copyright (C) 2010-2011 University of Oxford */

/* CCOPYRIGHT  */

#include "dwi_models.h"

#include "fwdmodel_dwi.h"
#include "fwdmodel_dwi_IVIM.h"

#include <fabber_core/fwdmodel.h>

extern "C" {
int CALL get_num_models()
{
    return 2;
}

const char *CALL get_model_name(int index)
{
    switch (index)
    {
    case 0:
        return "dwi";
        break;
    case 1:
        return "dwi_IVIM";
        break;
    default:
        return NULL;
    }
}

NewInstanceFptr CALL get_new_instance_func(const char *name)
{
    if (string(name) == "dwi")
    {
        return DWIFwdModel::NewInstance;
    }
    if (string(name) == "dwi_IVIM")
    {
        return DWI_IVIM_FwdModel::NewInstance;
    }
    else
    {
        return NULL;
    }
}
}
