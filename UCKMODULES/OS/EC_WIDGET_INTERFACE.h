#ifndef PROT_EC_WIDGET_INTERFACE_H_INCLUDED
#define PROT_EC_WIDGET_INTERFACE_H_INCLUDED
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc:
//============================================================================//
#include <string>
#include "BASE/ETYPES.h"
//============================================================================//
class EC_WIDGET_INTERFACE
{
public:
    si32            fOnInit(const wchar_t* wdgt_name);
public:
    bool            fIsEmpty();
public:
    si32            fWdgtCreate(si32 usrszx, si32 usrszy, bool brdr);
    si32            fWdgtShow();
    si32            fWdgtShow(bool value);
    si32            fWdgtHide();
    si32            fWdgtTitleSet(wchar_t* title);
    si32            fWdgtBorderSet(bool border);
    si32            fWdgtCursorShow(bool value);
    si32            fWdgtPositionSetUl(si32 posX, si32 posY);
    si32            fWdgtPositionSetMd(si32 posX, si32 posY);
    si32            fWdgtUserFrameSizeSet(si32 sizeX, si32 sizeY);
};
//============================================================================//

#endif // PROT_EC_WIDGET_INTERFACE_H_INCLUDED
