#include "SimMaker.h"
R__LOAD_LIBRARY(SimMaker_cxx)
void simmaker()
{
    SimMaker *maker = new SimMaker();
    maker->Init("problemA.root");
    maker->Make(1000000);
    maker->Finish();
}
