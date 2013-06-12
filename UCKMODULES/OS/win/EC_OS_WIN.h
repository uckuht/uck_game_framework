#ifndef PROT_OS_WIN_H_INCLUDED
#define PROT_OS_WIN_H_INCLUDED
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc:

#ifdef E_P_WIN

#include "../EC_OS_INTERFACE.h"
#include "EC_WIDGET_WIN.h"

class   EC_OS //: public EC_OS_INTERFACE
{
public:
    static si32     fOnUpdate();
    static si32     fMessageShow(const wchar_t* header, const wchar_t* body);
    static void     fSystemResolutionGet(si32* x, si32* y);
};

#endif // E_P_WIN

#endif // PROT_OS_WIN_H_INCLUDED
