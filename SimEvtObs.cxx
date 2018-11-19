#include "SimEvtObs.h"
ClassImp(SimEvtGen);
ClassImp(SimEvtObs);

SimEvtGen::~SimEvtGen()
{
}

SimEvtObs::SimEvtObs() : simevtgen(0)
{
    Float_t mptobs = 0;
    Float_t meobs = 0;
    Float_t mcosThetaobs = 0;

    Float_t mpterr = 0;
    Float_t meerr = 0;
    Float_t mcosThetaerr = 0;

    Float_t meres = 0;
    Float_t mthetares = 0;
}

SimEvtObs::SimEvtObs(SimEvtGen* evtgen)
{
    simevtgen = evtgen;

    Float_t mptobs = 0;
    Float_t meobs = 0;
    Float_t mcosThetaobs = 0;

    Float_t mpterr = 0;
    Float_t meerr = 0;
    Float_t mcosThetaerr = 0;

    Float_t meres = 0;
    Float_t mthetares = 0;
}

SimEvtObs::~SimEvtObs()
{
    if(simevtgen) delete simevtgen;
}

Int_t SimEvtObs::SetERes(Float_t res)
{
    if (simevtgen) {meres = res; return 0;}
    if (!simevtgen) { return -1; }
}

Int_t SimEvtObs::SetThetaRes(Float_t res)
{
    if (simevtgen) {mthetares = res; return 0;}
    if (!simevtgen) { return -1; }
}
