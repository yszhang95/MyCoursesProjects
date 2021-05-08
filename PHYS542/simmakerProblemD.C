#include "SimMaker.h"
R__LOAD_LIBRARY(SimMaker_cxx)
void simmakerProblemD()
{
    SimMaker *maker = new SimMaker();
    maker->Init("problemD.root");
    maker->Make(1000000, 0.8);
    maker->Finish();
}
