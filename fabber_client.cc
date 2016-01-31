/*  FABBER - Fast Diffusion Bayesian Estimation Routine

    Jesper Kallehauge, IBME

    Copyright (C) 2007-2016 University of Oxford  */

/*  CCOPYRIGHT */

#include "fabbercore/fabber_core.h"

// DWI models to be included from library
#include "fwdmodel_dwi.h"
#include "fwdmodel_dwi_IVIM.h"

int main(int argc, char** argv) {

  //add the CEST models - these will autoregister at this point
  DWIFwdModel::NewInstance();
  DWIF_IVIM_wdModel::NewInstance();
  
  return execute(argc, argv);

}