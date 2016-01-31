/*  fwdmodel_dwi.cc - Implements a convolution based model for DWI analysis

    Jesper Kallehauge, IBME

    Copyright (C) 2016 University of Oxford  */

/*  CCOPYRIGHT */

#include "fwdmodel_dwi.h"

#include <iostream>
#include <newmatio.h>
#include <stdexcept>
#include "newimage/newimageall.h"
using namespace NEWIMAGE;
#include "fabbercore/easylog.h"
#include "miscmaths/miscprob.h"

FactoryRegistration<FwdModelFactory, DWIFwdModel>
  DWIFwdModel::registration("dwi");

string DWIFwdModel::ModelVersion() const
{
  return "$Id: fwdmodel_dwi.cc,v 1.11 2016/01/06 15:20:47 Kallehauge Exp $";
}

void DWIFwdModel::HardcodedInitialDists(MVNDist& prior,
    MVNDist& posterior) const
{
    Tracer_Plus tr("DWIFwdModel::HardcodedInitialDists");
    assert(prior.means.Nrows() == NumParams());

     SymmetricMatrix precisions = IdentityMatrix(NumParams()) * 1e-12;

    // Set priors
    // Fp or Ktrans whatever you belive
     prior.means(ADC_index()) = 0.01;
     precisions(ADC_index(),ADC_index()) = 1e-12;

     prior.means(sig0_index()) = 0.01;
     precisions(sig0_index(),sig0_index()) = 1e-12;

    // Set precsions on priors
    prior.SetPrecisions(precisions);

    // Set initial posterior
    posterior = prior;

    // For parameters with uniformative prior chosoe more sensible inital posterior
    // Tissue perfusion
    posterior.means(ADC_index()) = 1;
    precisions(ADC_index(),ADC_index()) = 0.1;

    posterior.SetPrecisions(precisions);

}



void DWIFwdModel::Evaluate(const ColumnVector& params, ColumnVector& result) const
{
  Tracer_Plus tr("DWIFwdModel::Evaluate");

    // ensure that values are reasonable
    // negative check
   ColumnVector paramcpy = params;
    for (int i=1;i<=NumParams();i++) {
      if (params(i)<0) { paramcpy(i) = 0; }
      }

   // parameters that are inferred - extract and give sensible names
   float ADC;
   float sig0; //'inital' value of the signal

   // extract values from params
   sig0 = paramcpy(sig0_index());
   ADC = paramcpy(ADC_index());
   if (ADC<1e-8) ADC=1e-8;
   if (sig0<1e-8) sig0=1e-8;

   ColumnVector bvalshere; // the arterial signal to use for the analysis
   if (bvals.Nrows()>0) {
     bvalshere = bvals; //use the artsig that was loaded by the model
   }
   else {
     //use an artsig from supplementary data
     if (suppdata.Nrows()>0) {
       bvalshere = suppdata;
     }
     else {
       cout << "No valid b values found" << endl;
       throw;
     }
   }
   // use length of the aif to determine the number of time points
   int ntpts = bvalshere.Nrows();



   // --- Residue Function ----
   ColumnVector sig(ntpts);
   sig=0.0;

   sig = sig0*exp(-ADC*1e-3*bvals); // the 1 compartment model.
   //cout<<sig<<endl;
   result=sig;

   for (int i=1; i<=ntpts; i++) {
     if (isnan(result(i)) || isinf(result(i))) {
       exit(0);
       LOG << "Warning NaN of inf in result" << endl;
       LOG << "result: " << result.t() << endl;
       LOG << "params: " << params.t() << endl;

       result=0.0;
       break;
         }
   }


}

FwdModel* DWIFwdModel::NewInstance()
{
  return new DWIFwdModel();
}

void DWIFwdModel::Initialize(ArgsType& args)
{
  Tracer_Plus tr("DWIFwdModel::DWIFwdModel");
    string scanParams = args.ReadWithDefault("scan-params","cmdline");

    if (scanParams == "cmdline")
    {
      // specify command line parameters here
      //ColumnVector bvals;
      string bvalfile = args.Read("bvals");
    //cout<<bvalfile<<endl;
      if (bvalfile != "none") {
        bvals = read_ascii_matrix( bvalfile );
      }
    //cout<<bvalfile<<endl;
      doard=false;
     // if (inferart) doard=true;

      //imageprior = args.ReadBool("imageprior")
      // add information about the parameters to the log
      /* do logging here*/
    }

    else
        throw invalid_argument("Only --scan-params=cmdline is accepted at the moment");
}

vector<string> DWIFwdModel::GetUsage() const
{
  vector<string> usage;

  usage.push_back( "\nThis model is a one compartment model\n");
  usage.push_back( "It returns  2 parameters :\n");
  usage.push_back( " ADC: the Apparent Diffusion Coefficient\n");
  usage.push_back( " sig0: the initial signal\n");

  return usage;
}

void DWIFwdModel::DumpParameters(const ColumnVector& vec,
                                    const string& indent) const
{

}

void DWIFwdModel::NameParams(vector<string>& names) const
{
  names.clear();

  names.push_back("ADC");
  names.push_back("sig0");
}