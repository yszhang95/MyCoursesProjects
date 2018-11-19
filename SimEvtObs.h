#ifndef SimEvt_h
#define SimEvt_h

#include "TObject.h"

class TNtuple;

class SimEvtGen : public TObject {
public:
    SimEvtGen() {}; 
    virtual ~SimEvtGen();
    // void SetPt(Float_t pt) { mpt = pt; };
    // void SetE(Float_t e) { me = e; };
    // void SetCosTheta(Float_t cosTheta) { mcosTheta = cosTheta; };
    void SetPtPar(Float_t par) { mptpar = par; };
    void ClearInfo() { mptpar=0; mpt=0; me=0; mcosTheta=0; };
    Int_t Generate();
    Float_t GetPt() const {return mpt; } ;
    Float_t GetE() const {return me; } ;
    Float_t GetCosTheta() const {return mcosTheta; } ;

private:
    SimEvtGen& operator=(const SimEvtGen&);
    SimEvtGen(const SimEvtGen&);
    Float_t mptpar;
    Float_t mpt;
    Float_t me;
    Float_t mcosTheta;

    ClassDef(SimEvtGen, 1);
};

class SimEvtObs : public TObject{
  public:
    SimEvtObs();
    SimEvtObs(SimEvtGen*);
    virtual ~SimEvtObs();
    Int_t SetEResAndPar(Float_t);
    Int_t SetThetaErr(Float_t);
    Int_t SetPtErr();
    Int_t SetCosTheta(Float_t);
    Int_t SetE();
    Int_t SetE(Float_t);
    Int_t SetPt();
    Int_t SetPt(Float_t);

  private:
    SimEvtObs& operator=(const SimEvtGen&);
    SimEvtObs(const SimEvtGen&);    

    // variables of true event
    SimEvtGen* simevtgen;
    // variables of observed event
    Float_t mptobs;
    Float_t meobs;
    Float_t mcosThetaobs;
    // errors of observed variables
    Float_t mpterr;
    Float_t meerr;
    Float_t mcosThetaerr;
    // resolutions for detector
    Float_t merespar;

    ClassDef(SimEvtObs, 1)
};
#endif
