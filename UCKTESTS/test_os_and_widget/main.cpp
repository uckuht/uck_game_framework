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
    float   i = 30;
    int     j = (int)i;
    int     k = static_cast<int>(i);

    EC_OS       g_os;
    EC_WIDGET   g_wdgt;
    EC_RENDER   g_render;
    mLOG("Starting");
    g_wdgt.fOnInit(L"VSGE");
    g_wdgt.fRectSet(100, 100, 1200, 500);
    g_wdgt.fWdgtCreate(false);
    g_wdgt.fWdgtShow();
    EC_RENDER::INIT_STRUCT ini_str;

    ini_str.wdgt = g_wdgt.fHandlerGet();
    ini_str.bb_size.fClear();

    ES_DRAW_DATA draw_data;
    draw_data.fOnInitIndexedQuad(0,0,1,1,false,false,false);

//    draw_data.fOnInit( 4,0, false, true);
//
//    draw_data.fVertexPositionSet(0, -1,-1,0);
//    draw_data.fVertexPositionSet(1,  1,-1,0);
//    draw_data.fVertexPositionSet(2,  0, 1,0);
//    draw_data.fVertexPositionSet(3,  0, 1,0);
//
//    draw_data.fVertexColorSet(0,    ECOLOR_BLUE);
//    draw_data.fVertexColorSet(1,    ECOLOR_RED);
//    draw_data.fVertexColorSet(2,    ECOLOR_GREEN);
//    draw_data.fVertexColorSet(3,    ECOLOR_GREEN);

    ES_DRAW_OPTIONS draw_opt;
    draw_opt.fClear();
    draw_opt.fDiffuseSet(true);

    g_render.fOnInit(&ini_str);
    while(true)
    {//1
        g_os.fOnUpdate();

        g_render.fFrameClear(true, ECOLOR_BLUE,false,0,false ,0);
        if(EDONE == g_render.fFrameLock())
        {//1
            g_render.fDraw(&draw_data, &draw_opt);
            g_render.fFrameUnlock();
        }//1
        g_render.fFramePresent();
    }//1



    return EAPPNOERROR;
}
//============================================================================//
