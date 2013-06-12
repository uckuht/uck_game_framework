#ifdef E_P_WIN
#include "EC_WIDGET_WIN.h"
#include "BASE/ELANG.h"
#include "BASE/EMACRO.h"

//============================================================================//
LRESULT CALLBACK
DefWndProc(HWND hWnd, UINT msg, WPARAM wparam,LPARAM lparam)
{
    return DefWindowProc(hWnd,msg,wparam,lparam);
}
//============================================================================//
EC_WIDGET::EC_WIDGET()
{
    m_core = 0;
}
//============================================================================//
bool
EC_WIDGET::fIsEmpty()
{
    return m_wdgt_name.empty();
}
//============================================================================//
si32
EC_WIDGET::fOnInit(const wchar_t* wdgt_name)
{
    m_wdgt_name = wdgt_name;
    m_rect.fSet(0,0,100,100);
    return EDONE;
}
//============================================================================//
si32
EC_WIDGET::fWdgtCreate(bool brdr)
{
    if(fIsEmpty())
    {//1
        mLOGERROR("wdgt creation, class is empty");
        return EFAIL;
    }//1
mBLOCK("Wnd class init");
    WNDCLASSEXW wndcl;
    memset(&wndcl,0,sizeof(WNDCLASSEX));
    wndcl.lpszClassName = m_wdgt_name.c_str();
    wndcl.cbSize = sizeof(WNDCLASSEX);
    wndcl.hbrBackground = HBRUSH(4);
    wndcl.hInstance = GetModuleHandle(0);
    wndcl.hIcon = 0;
    wndcl.hIconSm = 0;
    wndcl.hCursor = LoadCursor(0,IDC_ARROW);
    wndcl.lpszMenuName = 0;
    wndcl.style = CS_HREDRAW | CS_VREDRAW;
    wndcl.cbWndExtra = 0;
    wndcl.cbClsExtra = 0;
    wndcl.lpfnWndProc = DefWndProc;

mBLOCK("Wnd class create");
    si32 hres = RegisterClassExW(&wndcl);
    if(!hres)
    {//1
        mLOGERROR("wdgt class creation");
        return EFAIL;
    }//1

mBLOCK("Window create");
    DWORD exstyle = 0;
    UINT  wnd_style = 0;
    if(!brdr)
    {//1
        wnd_style = WS_VISIBLE | WS_POPUP;
        exstyle = WS_EX_WINDOWEDGE;
    }//1
    m_core = CreateWindowExW(exstyle, m_wdgt_name.c_str(), L"", wnd_style, m_rect.x, m_rect.y, m_rect.w, m_rect.h, NULL, NULL, GetModuleHandle(0), this);
    if(!m_core)
    {//1
        mLOGERROR("wdgt creation");
        return EFAIL;
    }//1

    return EDONE;
}
//============================================================================//
si32
EC_WIDGET::fWdgtShow()
{
    ShowWindow(m_core,1);
    return EDONE;
}
//============================================================================//
si32
EC_WIDGET::fWdgtShow(bool value)
{
    ShowWindow(m_core, value);
    return EDONE;
}
//============================================================================//
si32
EC_WIDGET::fWdgtHide()
{
    ShowWindow(m_core,0);
    return EDONE;
}
//============================================================================//
si32
EC_WIDGET::fWdgtTitleSet(wchar_t* title)
{
    return EDONE;
}
//============================================================================//
si32
EC_WIDGET::fWdgtBorderSet(bool border)
{
    return EDONE;
}
//============================================================================//
si32
EC_WIDGET::fWdgtCursorShow(bool value)
{
    return EDONE;
}
//============================================================================//
si32
EC_WIDGET::fWdgtPositionSetUl(si32 posX, si32 posY)
{
    return EDONE;
}
//============================================================================//
si32
EC_WIDGET::fWdgtPositionSetMd(si32 posX, si32 posY)
{
    return EDONE;
}
//============================================================================//
si32
EC_WIDGET::fWdgtUserFrameSizeSet(si32 sizeX, si32 sizeY)
{
    return EDONE;
}
//============================================================================//
void
EC_WIDGET::fRectSet(si32 x, si32 y, si32 w, si32 h)
{
    m_rect.fSet(x,y,w,h);
}
//============================================================================//
void
EC_WIDGET::fPositionSet(si32 x, si32 y)
{
    m_rect.fPositionSet(x,y);
}
//============================================================================//
si32
EC_WIDGET::fWdgtRectAply()
{
    if(fIsEmpty())
        return EFAIL;

    BOOL op_res = SetWindowPos(m_core, HWND_TOP, m_rect.x, m_rect.y, m_rect.w, m_rect.h, SWP_NOZORDER);
    if(!op_res)
    {//1
        mLOGERROR("widget rect apply");
        return EFAIL;
    }//1
    return EDONE;
}
//============================================================================//
EWDGT
EC_WIDGET::fHandlerGet()
{
    return m_core;
}

//============================================================================//
#endif





















