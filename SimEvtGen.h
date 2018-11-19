#ifndef SimEvtGen_h
#define SimEvtGen_h

class SimEvtGen : public TObject {
public:
    SimEvtGen(); 
    virtual ~SimEvtGen();
    Int_t SetPt(Float_t pt) { mpt = pt; return 0; };
    Int_t SetE(Float_t e) { me = e; return 0; };
    Int_t SetCosTheta(Float_t cosTheta) { mcosTheta = cosTheta; return 0; };
    Int_t Clear() { mpt=0; me=0; mcosTheta=0; };
    const Float_t GetPt(){return mpt; } const;
    const Float_t GetE(){return me; } const;
    const Float_t GetCosTheta(){return mcosTheta; } const;

private:
    SimEvtGen& operator=(const SimEvtGen&);
    SimEvtGen(const SimEvtGen&);
    Float_t mpt;
    Float_t me;
    Float_t mcosTheta;

    ClassDef(SimEvtGen, 1);
};
#endif
