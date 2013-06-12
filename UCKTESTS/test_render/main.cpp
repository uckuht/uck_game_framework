#include "OS/OS.h"
#include "BASE/ELANG.h"
#include "BASE/EMACRO.h"

EC_OS       g_os;
EC_WIDGET   g_wdgt;

int
main()
{
    g_wdgt.fOnInit(L"VSGE");
    g_wdgt.fRectSet(100, 100, 300, 300);
    g_wdgt.fWdgtCreate(false);
    g_wdgt.fWdgtShow();
    
    while(true)
    {//1
        g_os.fOnUpdate();
    }//1
    return EAPPNOERROR;
}
