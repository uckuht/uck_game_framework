#ifndef PROT_ES_IRECT_H_INCLUDED
#define PROT_ES_IRECT_H_INCLUDED
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-28
// Desc: Целочисленная область.

struct ES_IRECT
{
    si32     x;
    si32     y;
    si32     w;
    si32     h;
public:
    void
    fSet(si32 x, si32 y, si32 w, si32 h)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }
    si32
    fWidthGet()
    {
        return w - x;
    }
    si32
    fHeightGet()
    {
        return h - y;
    }
    void
    fClear()
    {
        x = y = w = h = 0;
    }
    void
    fPositionMove(si32 x, si32 y)
    {
        this->x += x;
        this->y += y;
    }
    void
    fPositionSet(si32 x, si32 y)
    {
        this->x = x;
        this->y = y;
    }
};



#endif // PROT_ES_IRECT_H_INCLUDED
