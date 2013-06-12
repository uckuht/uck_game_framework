#ifndef PROT_ES_VECTOR3_H_INCLUDED
#define PROT_ES_VECTOR3_H_INCLUDED
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc:
//============================================================================//
#include "BASE/ETYPES.h"
//============================================================================//
struct  ES_VECTOR3
{
    sf32    x;
    sf32    y;
    sf32    z;
public:
    void    fSet(sf32 x, sf32 y, sf32 z);
};

#endif // PROT_ES_VECTOR3_H_INCLUDED
