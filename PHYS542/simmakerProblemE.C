#include "SimMaker.h"
R__LOAD_LIBRARY(SimMaker_cxx)
void simmakerProblemE()
{
    SimMaker *maker = new SimMaker();
    maker->Init("problemE.root");
    maker->Make(1000000, 0.8, true);
    maker->Finish();
}
