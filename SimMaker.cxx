#include "SimEvtObs.h"
#include "SimMaker.h"

#include "TNtuple.h"
#include "TH1F.h"
#include "TH2F.h"

SimMaker::SimMaker()
{
    simevtgen = 0;
    simevtobs = 0;
    t = 0;
    ptgen = 0;
    ptobs = 0;
    ptobsvsdiffpt = 0;
}

SimMaker::~SimMaker()
{
    if (simevtgen) delete simevtgen;
    if (simevtobs) delete simevtobs;
    if (t) delete t;
    if (ptgen) delete ptgen;
    if (ptobs) delete ptobs;
    if (ptobsvsdiffpt) delete ptobsvsdiffpt;
}

Int_t Init()
{
    Float_t par = 2; 
    SimEvtGen::SetPtPar(par);
    simevtgen = new SimEvtGen();
    simevtobs = new SimEvtObs(simevtgen);
}
