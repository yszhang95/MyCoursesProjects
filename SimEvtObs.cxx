#include "SimEvtObs.h"
#include "TMath.h"
#include "TRandom.h"
#include "TRandom3.h"

ClassImp(SimEvtGen);
ClassImp(SimEvtObs);

Int_t SimEvtGen::Generate()
{
    if(!mptpar) return -1;
    TRandom3 rpt, rtheta;
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
