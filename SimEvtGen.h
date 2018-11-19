#ifndef SimEvtGen_h
#define SimEvtGen_h

class SimEvtGen : public TObject {
public:
    SimEvtGen(); 
    SimEvtGen(Float_t pt, Float_t cosTheta);
    virtual ~SimEvtGen();
    Int_t SetPt(Float_t pt) {mpt = pt; return 0};
    Int_t SetE(Float_t e) {me = e; return 0};
    Int_t SetCosTheta(Float_t cosTheta) {mcosTheta = cosTheta; return 0};
    Int_t Clear() {mpt=0; e=0; cosTheta=0};
    const Float_t GetPt(return pt) const;
    const Float_t GetE(return e) const;
    const Float_t GetCosTheta(return cosTheta) const;

private:
    SimEvtGen& operator=(const SimEvtGen&);
    SimEvtGen(const SimEvtGen&);
    Float_t mpt;
    Float_t me;
    Float_t mcosTheta;

    ClassDef(SimEvtGen, 1);
}
#endif
