#ifndef PROT_EC_WIDGET_WIN_H_INCLUDED
#define PROT_EC_WIDGET_WIN_H_INCLUDED
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc:
//============================================================================//
#ifdef E_P_WIN
//============================================================================//
#include "../EC_WIDGET_INTERFACE.h"
#include "BASE/EPLATFORM.h"
#include "BASE/ES_IRECT.h"
//============================================================================//
class EC_WIDGET// : public EC_WIDGET_INTERFACE
{
    EWDGT           m_core;
    std::wstring    m_wdgt_name;
    ES_IRECT        m_rect;

public:
    EC_WIDGET();
    si32            fOnInit(const wchar_t* wdgt_name);
    void            fRectSet(si32 x, si32 y, si32 w, si32 h);
    void            fPositionSet(si32 x, si32 y);

public:
    si32            fWdgtCreate(bool brdr);
    si32            fWdgtShow();
    si32            fWdgtShow(bool value);
    si32            fWdgtHide();
    si32            fWdgtTitleSet(wchar_t* title);
    si32            fWdgtBorderSet(bool border);
    si32            fWdgtCursorShow(bool value);
    si32            fWdgtPositionSetUl(si32 posX, si32 posY);
    si32            fWdgtPositionSetMd(si32 posX, si32 posY);
    si32            fWdgtUserFrameSizeSet(si32 sizeX, si32 sizeY);
    si32            fWdgtRectAply();

public:
    bool            fIsEmpty();
    EWDGT           fHandlerGet();
};
//============================================================================//
#endif // E_P_WIN
#endif // EC_WIDGET_WIN_H_INCLUDED
