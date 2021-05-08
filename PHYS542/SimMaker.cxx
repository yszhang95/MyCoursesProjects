#include "SimMaker.h"

#include "TFile.h"
#include "TNtuple.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TString.h"
#include "TMath.h"
#include "TRandom.h"
#include "TRandom3.h"

#include <iostream>

ClassImp(SimEvtGen);
ClassImp(SimEvtObs);

Int_t SimEvtGen::Generate()
{
    if(!mptpar) return -1;
    TRandom3 rpt, rtheta;
    rpt.SetSeed(0);
    rtheta.SetSeed(0);
    mpt = rpt.Exp(mptpar);
    mcosTheta = rtheta.Uniform(0.9925461516, 0.9961946981);
    me = mpt / TMath::Sqrt(1 - mcosTheta*mcosTheta);
    return 0;
}

SimEvtGen::~SimEvtGen()
{
}

SimEvtObs::SimEvtObs() : simevtgen(0)
{
    mptobs = 0;
    meobs = 0;
    mcosThetaobs = 0;

    mpterr = 0;
    meerr = 0;
    mcosThetaerr = 0;

    merespar =0;
}

SimEvtObs::SimEvtObs(SimEvtGen* evtgen)
{
    simevtgen = evtgen;

    mptobs = 0;
    meobs = 0;
    mcosThetaobs = 0;

    mpterr = 0;
    meerr = 0;
    mcosThetaerr = 0;

    merespar =0;
}

SimEvtObs::~SimEvtObs()
{
    if(simevtgen) delete simevtgen;
}

void SimEvtObs::ClearInfo()
{
    mptobs = 0;
    meobs = 0;
    mcosThetaobs = 0;
    mpterr = 0;
    meerr = 0;
    mcosThetaerr = 0;
    merespar = 0;
}

Int_t SimEvtObs::Generate(Float_t par, Float_t costheta, Float_t costhetaerr)
{
    if(!simevtgen) return -1;
    SetEResParAndErr(par);
    SetE();
    SetCosTheta(costheta);
    SetPt();
    SetThetaErr(costhetaerr);
    SetPtErr();
    return 0;
}

Int_t SimEvtObs::GenerateWithTail(Float_t par, Float_t costheta, Float_t costhetaerr)
{
    if(!simevtgen) return -1;
    TRandom3 r;
    r.SetSeed(0);
    if(r.Uniform(0, 1)<0.03)
        SetEResParAndErr(5*par);
    else 
        SetEResParAndErr(par);
    SetE();
    SetCosTheta(costheta);
    SetPt();
    SetThetaErr(costhetaerr);
    SetPtErr();
    return 0;
}

Int_t SimEvtObs::SetEResParAndErr(Float_t par)
{
    if (simevtgen) {
        if(!par) return -1;
        merespar = par; 
        meerr = TMath::Sqrt(simevtgen->GetE()) * merespar;
        return 0;
    }
    return -1; 
}

Int_t SimEvtObs::SetThetaErr(Float_t err)
{
    if (simevtgen) {mcosThetaerr = err; return 0;}
    return -1;
}

Int_t SimEvtObs::SetCosTheta(Float_t costheta)
{
    if (simevtgen) {
        mcosThetaobs = costheta;
        return 0;
    }
    return -1;
}

Int_t SimEvtObs::SetE()
{
    if (simevtgen) {
        TRandom3 r;
        r.SetSeed(0);
        if (!meerr) return -1;
        meobs = r.Gaus(simevtgen->GetE(), meerr);
        return 0;
    }
    return -1;
}

Int_t SimEvtObs::SetE(Float_t e)
{
    if (simevtgen) {
        meobs = e;
        return 0;
    }
    return -1;
}

Int_t SimEvtObs::SetPt()
{
    if (simevtgen){
        if(!meobs) return -1;
        mptobs = meobs * TMath::Sqrt(1 - mcosThetaobs * mcosThetaobs);
        return 0;
    }
    return -1;
}

Int_t SimEvtObs::SetPt(Float_t pt)
{
    if (simevtgen) {
        mptobs = pt;
        return 0;
    }
    return -1;
}
Int_t SimEvtObs::SetPtErr()
{
    if (simevtgen) {
        Float_t sumw2 = 0;
        Float_t sinTheta = TMath::Sqrt(1 - mcosThetaobs *mcosThetaobs);
        Float_t err1 = mcosThetaobs * meobs / sinTheta; 
        sumw2 += TMath::Power(err1, 2);
        Float_t err2 = sinTheta * meerr;
        sumw2 += TMath::Power(err2, 2);
        mpterr = TMath::Sqrt(sumw2);
        return 0;
    }
    return -1;
}

SimMaker::SimMaker()
{
    simevtgen = 0;
    simevtobs = 0;
    f = 0;
    t = 0;
    hptgen = 0;
    hptobs = 0;
    hptobsvsdiffpt = 0;
    hegenvseobs = 0;
}

SimMaker::~SimMaker()
{
    if (simevtobs) delete simevtobs;
    //if (t) delete t;
    //if (hptgen) delete hptgen;
    //if (hptobs) delete hptobs;
    //if (hptobsvsdiffpt) delete hptobsvsdiffpt;
}

Int_t SimMaker::Init(TString filename = "sample.root")
{
    Float_t par = 2; 
    SimEvtGen::SetPtPar(par);
    simevtgen = new SimEvtGen();
    simevtobs = new SimEvtObs(simevtgen);
    f = new TFile(filename.Data(), "recreate");
    f->cd();
    TString varlist = "ptgen:egen:costhetagen:"
                       "ptobs:eobs:costhetaobs:"
                       "pterr:eerr:costhetaerr:erespar";
    t = new TNtuple("simevt", "simevt", varlist.Data(), 2^31);
    hptgen = new TH1F("ptgen", "ptgen", 100, 0, 10);
    hptobs = new TH1F("ptobs", "ptobs", 100, 0, 10);
    hptobsvsdiffpt = new TH2F("ptobsvsdiffpt", "ptobsvsdiffpt",20, 10, 10, 100, 0, 10);
    hegenvseobs = new TH2F("egenvseobs", "egenvseobs",200, 0, 100, 200, 0, 100);
    return 0;
}

Int_t SimMaker::MakeEvent(Float_t epar, Bool_t tail = false)
{
    if (!simevtgen) return -1;
    simevtgen->ClearInfo();
    simevtgen->Generate();
    simevtobs->ClearInfo();
    if(!tail) simevtobs->Generate(epar, 0.9943704249 , 0.001);
    if(tail) simevtobs->GenerateWithTail(epar, 0.9943704249, 0.001);

    Float_t vararray[10];
    Int_t i=0;
    vararray[i++] = simevtgen->GetPt();
    vararray[i++] = simevtgen->GetE();
    vararray[i++] = simevtgen->GetCosTheta();
    vararray[i++] = simevtobs->GetPtObs();
    vararray[i++] = simevtobs->GetEObs();
    vararray[i++] = simevtobs->GetCosThetaObs();
    vararray[i++] = simevtobs->GetPtErr();
    vararray[i++] = simevtobs->GetEErr();
    vararray[i++] = simevtobs->GetCosThetaErr();
    vararray[i++] = simevtobs->GetEResPar();
    t->Fill(vararray);

    hptgen->Fill(simevtgen->GetPt());
    hptobs->Fill(simevtobs->GetPtObs());

    Float_t diffpt = simevtgen->GetPt() - simevtobs->GetPtObs();
    hptobsvsdiffpt->Fill(simevtgen->GetPt(), diffpt);

    hegenvseobs->Fill(simevtgen->GetE(), simevtobs->GetEObs());

    return 0;
}

Int_t SimMaker::Make(Int_t noevt, Float_t epar, Bool_t tail=false)
{
    for(int i=0; i<noevt; ++i){
        MakeEvent(epar, tail);
        if (i%100000==0) std::cout << i/100000 << "e5" << std::endl;
    }
    return 0;
}

Int_t SimMaker::Finish()
{
    if(!f) return -1;
    f->cd();
    t->Write();
    hptgen->Write();
    hptobs->Write();
    hptobsvsdiffpt->Write();
    hegenvseobs->Write();
//    f->Close();
    return 0;
}
