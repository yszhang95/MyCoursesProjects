#include "SimMaker.h"
R__LOAD_LIBRARY(SimMaker_cxx)
void simmakerProblemA()
{
    SimMaker *maker = new SimMaker();
    maker->Init("problemA.root");
    maker->Make(1000000, 0.1);
    maker->Finish();
}
