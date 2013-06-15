#ifndef PROT_EC_RENER_H_INCLUDED
#define PROT_EC_RENER_H_INCLUDED
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc: Модуль рендера DirectX9c.
//============================================================================//
#include <map>
//============================================================================//
#include "BASE/EPLATFORM.h"
#include "BASE/ES_POINT2.h"
#include "BASE/ES_VECTOR4.h"
#include "BASE/ES_TRANSFORM.h"
//============================================================================//
#include "RENDER/RENDER_DX/ADDON/Include/d3d9.h"
#include "RENDER/RENDER_DX/ADDON/Include/d3dx9.h"
//============================================================================//
struct ES_DRAW_DATA;
struct ES_DRAW_OPTIONS;
//============================================================================//
class EC_RENDER
{
public:
    struct INIT_STRUCT
    {
        EWDGT       wdgt;
        ES_POINT2   bb_size;
    };

public:// инициализация
    EC_RENDER();

public:
    si32     fOnInit(INIT_STRUCT* p_init);

public:// искажения

public:// рисование
    si32    fFrameClear(bool pixels, ui32 color, bool z_order, sf32 zvalue, bool stencil, ui16 svalue);
    si32    fFrameLock();
    si32    fFrameUnlock();
    si32    fFramePresent();
    si32    fDraw(ES_DRAW_DATA* p_data, ES_DRAW_OPTIONS* p_options);

private:
    struct LOGIC
    {
        IDirect3DDevice9Ex*     device;
        D3DPRESENT_PARAMETERS   present;
        D3DXMATRIX              mx_world;
        D3DXMATRIX              mx_viev;
        D3DXMATRIX              mx_proj;

        ES_TRANSFORM            tr_local;
        ES_TRANSFORM            tr_global;

        ES_VECTOR4              eye_pos;
        ES_VECTOR4              eye_up;
        ES_VECTOR4              eye_at;
    }m_logic;
    struct VB
    {
        ui32                        vb_format;
        ui32                        vb_size;
        LPDIRECT3DVERTEXBUFFER9     vb;
    };
    typedef std::pair<ui32, VB>     TP_VB; // format, vertex buffer
    typedef std::map<ui32, VB>      MAP_VB;
    MAP_VB                          buffers;// preparied buffers
    struct RASTER
    {
        LPDIRECT3DVERTEXBUFFER9     vertex_buffer;
        ui32                        vertex_buffer_size;
        LPDIRECT3DINDEXBUFFER9      index_buffer;
        ui32                        index_buffer_size;
        ui32                        raster_format;
        ui32                        vertex_count;
        ui32                        primitive_count;
        ui32                        total_size;
        ui32                        vertex_size;
    }m_raster;

private:
    void                sInitMatrixes();
    IDirect3D9Ex*       sDriverGet();
    si32                sDrawRasterData();
    void                sRaserDataClear();
    si32                sBufferCreate(ui32 vertex_buffer_size, ui32 vertex_buffer_format, ui32 index_buffer_size);
    VB*                 sVBCheck(ui32 format);// check vertex buffer by format
    VB*                 sVBCreate(ui32 format, ui32 total_size);
};

#endif // EC_RENER_H_INCLUDED
