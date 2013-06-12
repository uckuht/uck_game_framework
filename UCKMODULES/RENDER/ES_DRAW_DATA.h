#ifndef PROT_EC_DRAW_DATA_H
#define PROT_EC_DRAW_DATA_H
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc:
//============================================================================//
#include "BASE/ETYPES.h"
//============================================================================//
struct ES_VECTOR3;
//============================================================================//
struct ES_DRAW_DATA
{
    ui32  vertex_format;
    ui32  vertex_count;
    sf32* positions;
    sf32* texels;
    ui32* colors;
    sf32* normals;
    ui16  index_count;
    ui16* indexes;
    void* render_descriptor;

public:
    ES_DRAW_DATA();
public:
    si32            fOnInit(ui32 v_cnt, ui32 i_cnt = 0, bool tex = false, bool col = false, bool nor = false);
    si32            fOnInitIndexedQuad(sf32 x, sf32 y, sf32 w, sf32 h, bool tex, bool col, bool nor);
public:
    si32            fVertexPositionSet(ui32 num, sf32 x, sf32 y, sf32 z = 0);
    si32            fVertexColorSet(ui32 num, ui32 color);
    si32            fIndexValueSet(ui32 num, ui16 value);
public:
    ES_VECTOR3*     fPositionGet(ui32 num);// Unsafe
    ui32*           fColorGet(ui32 num)   ;// Unsafe
public:
    ui32            fVertexSizeOfGet(bool tex = 0, bool col = 0, bool nor = 0);
    ui32            fVertexCountGet();
};


#endif // PROT_EC_DRAW_DATA_H
