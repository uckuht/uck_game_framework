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
#define E_RENDER_INDEX_TYPE ui16
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
    si32    fEyeSet(sf32 x, sf32 y, sf32 z, sf32 ux, sf32 uy, sf32 uz, sf32 tx, sf32 ty, sf32 tz);
    si32    fProjectionPerspectiveSet(ui32 scrW = 0, ui32 scrH = 0);
    si32    fProjectionOrthogonalSet(ui32 scrW = 0, ui32 scrH = 0, bool left_hand = false);

    si32    fTransformGlobalSet(ES_TRANSFORM* p_transform);
    si32    fTransformGlobalAdd(ES_TRANSFORM* p_transform);

    si32    fTransformLocalSet(ES_TRANSFORM* p_transform);

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

        D3DXMATRIX              mx_global;
        D3DXMATRIX              mx_local;

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
    typedef std::pair<ui32, VB>                 TP_VB; // format, vertex buffer
    typedef std::map<ui32, VB>                  MAP_VB;
    typedef std::map<ui32, VB>::iterator        MAP_VB_ITER;
    MAP_VB                                      m_buffers;// preparied buffers
    struct RASTER
    {
        LPDIRECT3DVERTEXBUFFER9     vertex_buffer;
        ui32                        vertex_count;
        ui32                        vertex_buffer_size;
        LPDIRECT3DINDEXBUFFER9      index_buffer;
        ui32                        index_count;
        ui32                        index_buffer_size;
        ui32                        raster_format;
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
    si32                sVBExpand(VB* buffer, ui32 new_size);
    si32                sIBCreate(ui32 index_b_size);
    si32                sIBExpand(ui32 new_size);
    si32                sRasterFill(VB* p_filler, ES_DRAW_DATA* p_data, ui32 data_size,bool tex, bool col, bool nor);
    ui32                sRasterFormatGet(bool tex, bool col, bool nor);
    si32                sTransformToMatrix(ES_TRANSFORM* p_transform, D3DXMATRIX* p_matrix);
    si32                sWorldMatrixSet(D3DXMATRIX* mx_world);

};

#endif // EC_RENER_H_INCLUDED
