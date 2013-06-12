#ifndef PROT_ES_VECTOR_H_INCLUDED
#define PROT_ES_VECTOR_H_INCLUDED
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc: вектор пространства. Может выступать в роли позиции(w = 1), направления(w = 0), квартерниона и момента поворота.
// Отличительная особенность - удобно умножается на матрицу, оптимально исользуется шейдером.
#include "BASE/ETYPES.h"
//============================================================================//
struct  ES_VECTOR4
{
    sf32   x;
    sf32   y;
    sf32   z;
    sf32   w;
};

#endif // ES_VECTOR_H_INCLUDED
