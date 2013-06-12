#ifndef PROT_ES_TEXTURE_DATA
#define PROT_ES_TEXTURE_DATA
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc: то что нужно знать о текстуре. формат может быть разный, соотв пиксель может иметь разный размер.
//============================================================================//
#include "BASE/ES_POINT2.h"
//============================================================================//
struct ES_TEXTURE_DATA
{
    ui64        texture;    // дескриптор текстуры в драйвере
    ES_POINT2   tex_size;   // размер текстуры в пикселях
    ui32        tex_type;   // формат текстуры
    void*       tex_data;   // бинарные данные т.е пиксели
};

#endif // PROT_ES_TEXTURE_DATA
