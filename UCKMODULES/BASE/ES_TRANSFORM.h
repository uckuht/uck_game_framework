#ifndef PROT_ES_TRANSFORM_H_INCLUDED
#define PROT_ES_TRANSFORM_H_INCLUDED
// This file a part of project uckegine
// All staff as is ...
// Autor: UCKUHT
// Date: 2013-05-17
// Desc:

struct ES_TRANSFORM
{
// local
    // translate
    sf32            tx;
    sf32            ty;
    sf32            tz;
    // scale
    sf32            sx;
    sf32            sy;
    sf32            sz;
    // rotation
    sf32            rx;
    sf32            ry;
    sf32            rz;
    // center(hot_spot, pevod)
    sf32            cx;
    sf32            cy;
    sf32            cz;
// global(include parent)
    sf32            gtx;
    sf32            gty;
    sf32            gtz;
    sf32            gsx;
    sf32            gsy;
    sf32            gsz;
    sf32            grx;
    sf32            gry;
    sf32            grz;
    sf32            gcx;
    sf32            gcy;
    sf32            gcz;
    ES_TRANSFORM*   parent;
    void*           owner;
    ui32            hash;
    
public:
    void
    fClear()
    {
        memset(this,0,sizeof(ES_TRANSFORM));
        sx = sy = sz = 1;
    }
};

#endif // PROT_ES_TRANSFORM_H_INCLUDED
