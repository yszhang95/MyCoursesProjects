#ifndef SimMaker_h
#define SimMaker_h

#include "TObject.h"

class TNtuple;
class TH1F;
class TH2F;

class SimEvtGen : public TObject {
private:
    SimEvtGen& operator=(const SimEvtGen&);
    SimEvtGen(const SimEvtGen&);
    static Float_t mptpar;
    Float_t mpt;
    Float_t me;
    Float_t mcosTheta;

public:
    SimEvtGen() { mpt=0; me=0; mcosTheta=0;}; 
    virtual ~SimEvtGen();
    // void SetPt(Float_t pt) { mpt = pt; };
    // void SetE(Float_t e) { me = e; };
    // void SetCosTheta(Float_t cosTheta) { mcosTheta = cosTheta; };
    static void SetPtPar(const Float_t par) { mptpar = par; };
    void ClearInfo() { mpt=0; me=0; mcosTheta=0; };
    Int_t Generate();
    Float_t GetPt() const {return mpt; } ;
    Float_t GetE() const {return me; } ;
    Float_t GetCosTheta() const {return mcosTheta; } ;

    ClassDef(SimEvtGen, 1);
};

Float_t SimEvtGen::mptpar = 0;

class SimEvtObs : public TObject{
  public:
    SimEvtObs();
    SimEvtObs(SimEvtGen*);
    virtual ~SimEvtObs();

    void ClearInfo();
    Int_t Generate(Float_t, Float_t, Float_t);

    Int_t SetEResParAndErr(Float_t);
    Int_t SetThetaErr(Float_t);
    Int_t SetPtErr();
    Int_t SetCosTheta(Float_t);
    Int_t SetE();
    Int_t SetE(Float_t);
    Int_t SetPt();
    Int_t SetPt(Float_t);
    Float_t GetPtObs() const { return mptobs; };
    Float_t GetPtErr() const { return mpterr; };
    Float_t GetEObs() const { return meobs; };
    Float_t GetEErr() const { return meerr; };
    Float_t GetCosThetaObs() const { return mcosThetaobs; };
    Float_t GetCosThetaErr() const { return mcosThetaerr; };
    Float_t GetEResPar()const { return merespar; };

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

class SimMaker
{
  private:
    Int_t MakeEvent();

    SimEvtGen *simevtgen;
    SimEvtObs *simevtobs;
    TNtuple *t;
    TH1F* hptgen;
    TH1F* hptobs;
    TH2F* hptobsvsdiffpt;

  public:
    SimMaker();
    Int_t Init();
    Int_t Make(Int_t);
    virtual ~SimMaker();
};

#endif
