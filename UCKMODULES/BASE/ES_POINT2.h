#ifndef PROT_ES_POINT2
#define PROT_ES_POINT2
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-28
// Desc: Точка в 2х мерном пространстве. Оптимальна для работы с пикселями.
#include "BASE/ETYPES.h"
//============================================================================//
struct ES_POINT2
{
    si32     x;
    si32     y;
public:
    void
    fClear()
    {
        x = y = 0;
    }
    void
    fSet(si32 x, si32 y)
    {
        this->x = x;
        this->y = y;
    }
};



#endif // ES_POINT2_H_INCLUDED
