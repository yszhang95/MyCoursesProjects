#include "SimMaker.h"
R__LOAD_LIBRARY(SimMaker_cxx)
void simmakerProblemF()
{
    SimMaker *maker = new SimMaker();
    maker->Init("problemF.root");
    maker->Make(1000000, 0.03);
    maker->Finish();
}
