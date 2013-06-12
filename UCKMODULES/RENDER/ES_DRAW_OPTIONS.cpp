#include <string.h>
#include "ES_DRAW_OPTIONS.h"
//=================================================================//
void
ES_DRAW_OPTIONS::fClear()
{
    memset(this,0,sizeof(ES_DRAW_OPTIONS));
}
//=================================================================//
void
ES_DRAW_OPTIONS::fDiffuseSet(bool value)
{
    diffused = value;
}

//=================================================================//
