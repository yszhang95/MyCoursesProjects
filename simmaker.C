#include "SimMaker.h"
R__LOAD_LIBRARY(SimMaker_cxx)
void simmaker()
{
    SimMaker *maker = new SimMaker();
    maker->Init();
    maker->Make(5000000);
    maker->Finish();
}
