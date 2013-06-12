#ifndef PROT_ES_DRAW_OPTIONS_H
#define PROT_ES_DRAW_OPTIONS_H
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc: опции рисования для рендера
//============================================================================//
#include "BASE/ETYPES.h"
//============================================================================//
struct ES_DRAW_OPTIONS
{
    bool    texured;    // текстурируется
    bool    blended;    // смешивается(альфа)
    bool    diffused;   // используются цвета вершин
    bool    normaled;   // используются нормали
    bool    zordered;   // z буффер включен
    ui16    prim_type;
    ui16    effect;
public:
    void    fClear();
    void    fDiffuseSet(bool value);
};
#endif // PROT_ES_DRAW_OPTIONS_H
