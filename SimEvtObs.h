#ifndef SimEvtObs_h
#define SimEvtObs_h

class SimEvtGen;
class TNtuple;

class SimEvtObs : public TObject{
  public:
    SimEvtObs();
    SimEvtObs(SimEvtGen*);
    SetERes(Float_t );
    ~virtual SimEvtObs();

  private:
    SimEvtObs& operator=(const SimEvtGen&);
    SimEvtObs(const SimEvtGen&);    

    // variables of true event
    Float_t mptgen;
    Float_t megen;
    Float_t mcosThetagen;
    // variables of observed event
    Float_t mptobs;
    Float_t meobs;
    Float_t mcosThetaobs;
    // errors of observed variables
    Float_t mpterr;
    Float_t meerr;
    Float_t mcosThetaerr;
    // tree for storage
    TNtuple* nt;

    ClassDef(SimEvtObs, 1)
};
#endif
