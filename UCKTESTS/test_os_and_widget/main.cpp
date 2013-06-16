#include "OS/OS.h"
#include "RENDER/RENDER.h"
#include "BASE/ELANG.h"
#include "BASE/EMACRO.h"
#include "RENDER/ES_DRAW_DATA.h"
#include "RENDER/ES_DRAW_OPTIONS.h"
//============================================================================//

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------

//============================================================================//
int
main()
{

    EC_OS       g_os;
    EC_WIDGET   g_wdgt;
    EC_RENDER   g_render;
    mLOG("Starting");
    g_wdgt.fOnInit(L"VSGE");
    g_wdgt.fRectSet(600, 100, 800, 600);
    g_wdgt.fWdgtCreate(false);
    g_wdgt.fWdgtShow();
    EC_RENDER::INIT_STRUCT ini_str;

    ini_str.wdgt = g_wdgt.fHandlerGet();
    ini_str.bb_size.fClear();

    ES_DRAW_DATA draw_data;
    draw_data.fOnInitIndexedQuad(-2,-1,1,1,false,true,false);

    draw_data.fVertexColorSet(0,    ECOLOR_BLUE);
    draw_data.fVertexColorSet(1,    ECOLOR_BLUE);
    draw_data.fVertexColorSet(2,    ECOLOR_BLUE);
    draw_data.fVertexColorSet(3,    ECOLOR_BLUE);

    ES_DRAW_DATA    ano_data;
    ano_data.fOnInitIndexedQuad(-1,-1,2,2,false,false,false);

    ES_DRAW_OPTIONS draw_opt;
    draw_opt.fClear();
    draw_opt.fDiffuseSet(true);

    g_render.fOnInit(&ini_str);
    while(true)
    {//1
        g_os.fOnUpdate();

        g_render.fFrameClear(true, ECOLOR_GRAY,false,0,false ,0);
        if(EDONE == g_render.fFrameLock())
        {//1
            g_render.fDraw(&draw_data,  &draw_opt);
            g_render.fDraw(&ano_data,   &draw_opt);
            g_render.fFrameUnlock();
        }//1
        g_render.fFramePresent();
    }//1



    return EAPPNOERROR;
}
//============================================================================//
