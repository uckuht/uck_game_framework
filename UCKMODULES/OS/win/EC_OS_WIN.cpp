#include "EC_OS_WIN.h"
#include "BASE/ELANG.h"
//============================================================================//
int
EC_OS::fOnUpdate()
{
    MSG msg;
    memset(&msg,0,sizeof(MSG));
    while(PeekMessageW(&msg,0,0,0,PM_REMOVE))
    {//1
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }//1
    return EDONE;
}
//============================================================================//
