/*  fwdmodel_dwi.h - Implements the GRASE model

    Jesper Kallehauge, IBME

    Copyright (C) 2007-2016 University of Oxford  */

/*  CCOPYRIGHT */

#include "fabbercore/fwdmodel.h"
#include "fabbercore/inference.h"
#include <string>
using namespace std;

class DWIFwdModel : public FwdModel {
public:
  static FwdModel* NewInstance();

  // Virtual function overrides
  virtual void Initialize(ArgsType& args);
  virtual void Evaluate(const ColumnVector& params,
                  ColumnVector& result) const;
  virtual vector<string> GetUsage() const;
  virtual string ModelVersion() const;

  virtual void DumpParameters(const ColumnVector& vec,
                                const string& indents = "") const;

  virtual void NameParams(vector<string>& names) const;
  virtual int NumParams() const
  { return 2; }

  virtual ~DWIFwdModel() { return; }

  virtual void HardcodedInitialDists(MVNDist& prior, MVNDist& posterior) const;

protected:


// Constants

  // Lookup the starting indices of the parameters
  int ADC_index() const {return 1;}

  int sig0_index() const { return 2; }

  //for ARD
  vector<int> ard_index;

  bool doard;
  ColumnVector bvals;

  private:
  /** Auto-register with forward model factory. */
  static FactoryRegistration<FwdModelFactory, DWIFwdModel> registration;

};