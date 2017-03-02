/*  FABBER - Fast Diffusion Bayesian Estimation Routine

    Jesper Kallehauge, IBME

    Copyright (C) 2007-2016 University of Oxford  */

/*  CCOPYRIGHT */

#include "fabber_core/fabber_core.h"

// DWI models to be included from library
#include "fwdmodel_dwi.h"
#include "fwdmodel_dwi_IVIM.h"

int main(int argc, char **argv)
{
    return execute(argc, argv);
}