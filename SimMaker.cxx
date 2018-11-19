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

Int_t SimMaker::Init()
{
    Float_t par = 2; 
    SimEvtGen::SetPtPar(par);
    simevtgen = new SimEvtGen();
    simevtobs = new SimEvtObs(simevtgen);
    t = new TNtuple("simevt", "simevt");
    ptgen = new TH1F("ptgen", "ptgen", 100, 0, 10);
    ptobs = new TH1F("ptobs", "ptobs", 100, 0, 10);
}

Int_t SimMaker::MakeEvent()
{
    if (!simevtgen) return -1;
    simevtgen->ClearInfo();
    simevtgen->Generate();
}
