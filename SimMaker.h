#ifndef SimMaker_h
#define SimMaker_h

class TNtuple;
class TH1F;
class TH2F;
class SimEvtGen;
class SimEvtObs;

class SimMaker
{
  private:
    SimEvtGen *simevtgen;
    SimEvtObs *simevtobs;
    TNtuple *t;
    TH1F* ptgen;
    TH1F* ptobs;
    TH2F* ptobsvsdiffpt;

  public:
    SimMaker();
    Int_t Init();
    virtual ~SimMaker();
};

#endif
