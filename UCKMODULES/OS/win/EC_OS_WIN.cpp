#include "EC_OS_WIN.h"
#include "BASE/ELANG.h"
//============================================================================//
int
EC_OS::fOnUpdate()
{
    MSG msg;
    if(GetMessageW(&msg,0,0,0))
    {//1
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }//1
    return EDONE;
}
//============================================================================//
