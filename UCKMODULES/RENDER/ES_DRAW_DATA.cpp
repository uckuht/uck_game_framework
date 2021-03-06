//============================================================================//
#include <string.h>
//============================================================================//
#include "ES_DRAW_DATA.h"
#include "BASE/ELANG.h"
#include "BASE/EMACRO.h"
#include "BASE/ES_VECTOR3.h"
//============================================================================//
ES_DRAW_DATA::ES_DRAW_DATA()
{
    memset(this,0,sizeof(ES_DRAW_DATA));
}
//============================================================================//
si32
ES_DRAW_DATA::fOnInit(ui32 v_cnt, ui32 i_cnt, bool tex, bool col, bool nor)
{// создать необходимые массивы

    vertex_count = v_cnt;
    index_count  = i_cnt;
    // x y z
    positions = new sf32[vertex_count * 3];
    if(tex)
    {//1 по количеству координат
        texels = new sf32[vertex_count * 2];
    }//1
    if(col)
    {//1 количество цветов совпадает с количеством вершин
        colors = new ui32[vertex_count];
    }//1
    if(nor)
    {//1 nx ny nz
        normals = new sf32[vertex_count * 3];
    }//1
    if(index_count)
    {//1
        indexes = new ui16[index_count];
    }//1

    return EDONE;
}
//============================================================================//
si32
ES_DRAW_DATA::fVertexPositionSet(ui32 num, sf32 x, sf32 y, sf32 z)
{
    if(num > vertex_count - 1)
    {//1
        mLOGWARN("getting access to unexisting vertex");
        return EFAIL;
    }//1
    ES_VECTOR3* p_position = fPositionGet(num);
    p_position->fSet(x,y,z);
    return EDONE;
}
//============================================================================//
ES_VECTOR3*
ES_DRAW_DATA::fPositionGet(ui32 num)
{
    return (ES_VECTOR3*)&positions[num*3];
}
//=================================================================//
ui32
ES_DRAW_DATA::fVertexSizeOfGet(bool tex, bool col, bool nor)
{
    ui32 size_of = 3 * sizeof(sf32);
    if(tex)
    {//1
        size_of += 2 * sizeof(sf32);
    }//1
    if(col)
    {//1
        size_of += 1 * sizeof(ui32);
    }//1
    if(nor)
    {//1
        size_of += 3 * sizeof(sf32);
    }//1
    return size_of;
}

//============================================================================//
ui32
ES_DRAW_DATA::fVertexCountGet()
{
    return vertex_count;
}
//=================================================================//
si32
ES_DRAW_DATA::fVertexColorSet(ui32 num, ui32 color)
{
    if(NULL == colors )
    {//1
        return ENOTHING;
    }//1
    if(num > vertex_count - 1)
    {//1
        mLOGWARN("getting access to unexisting color");
        return EFAIL;
    }//1
    ui32* col = fColorGet(num);
    *col = color;
    return EDONE;
}
//=================================================================//
ui32*
ES_DRAW_DATA::fColorGet(ui32 num)
{
    return &colors[num];
}
//=================================================================//
si32
ES_DRAW_DATA::fOnInitIndexedQuad(sf32 x, sf32 y, sf32 w, sf32 h, bool tex, bool col, bool nor)
{
    fOnInit( 4, 6, tex, col, nor);
    fVertexPositionSet(0, x,        y,      0);
    fVertexPositionSet(1, x + w,    y,      0);
    fVertexPositionSet(2, x + w,    y + h,  0);
    fVertexPositionSet(3, x,        y + h,  0);

    fIndexValueSet(0,0);
    fIndexValueSet(1,1);
    fIndexValueSet(2,2);
    fIndexValueSet(3,0);
    fIndexValueSet(4,2);
    fIndexValueSet(5,3);

    return EDONE;
}
//============================================================================//
si32
ES_DRAW_DATA::fIndexValueSet(ui32 num, ui16 value)
{
    if(NULL == indexes)
    {//1
        mLOGERROR("no indexes in draw data");
        return EFAIL;
    }//1
    if(num > index_count)
    {//1
        mLOGERROR("accessing to unexisting index");
        return EFAIL;
    }//1

    indexes[num] = value;
    return EDONE;
}
//============================================================================//












