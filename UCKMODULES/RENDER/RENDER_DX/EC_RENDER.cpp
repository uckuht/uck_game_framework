#include <string>
//============================================================================//
#include "RENDER/RENDER_DX/ADDON/Include/d3d9.h"
#include "RENDER/RENDER_DX/ADDON/Include/d3dx9.h"
//============================================================================//
#include "RENDER/ES_DRAW_DATA.h"
#include "RENDER/ES_DRAW_OPTIONS.h"
#include "EC_RENDER.h"
#include "BASE/EMACRO.h"
#include "BASE/ELANG.h"
//============================================================================//
EC_RENDER*              context = 0;// контекст всегда один
std::string             context_error;// возможно тут будет сохраняться текст ошибки
IDirect3D9Ex*           directx = 0;
LPDIRECT3DVERTEXBUFFER9 p_vb = 0;



IDirect3D9*           g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9     g_pd3dDevice = NULL; // Our rendering device
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL; // Buffer to hold vertices

// A structure for our custom vertex type
struct CUSTOMVERTEX
{
    FLOAT x, y, z;
};

// Our custom FVF, which describes our custom vertex structure
ui32 D3DFVF_CUSTOMVERTEX = D3DFVF_XYZ;
    CUSTOMVERTEX g_Vertices[] =
    {
        { -1.0f,-1.0f, 0.0f, },
        {  1.0f,-1.0f, 0.0f, },
        {  0.0f, 1.0f, 0.0f, },
    };

//============================================================================//
IDirect3D9Ex*
EC_RENDER::sDriverGet()
{// инициализация драйвера
    if(NULL == directx)
        if(FAILED( Direct3DCreate9Ex(D3D_SDK_VERSION,&directx)))
        {//1
            mLOGERROR("direct x creation");
            return NULL;
        }//1

    return directx;
}
//=================================================================//
EC_RENDER::EC_RENDER()
{
    m_logic.device = 0;
}
//============================================================================//
si32
EC_RENDER::fOnInit(INIT_STRUCT* p_init)
{
    IDirect3D9Ex* driver = sDriverGet();
    if(!driver)
    {//1
        return EFAIL;
    }//1

    D3DPRESENT_PARAMETERS& pp       = m_logic.present;
    memset(&m_logic.present, 0, sizeof(D3DPRESENT_PARAMETERS));
    pp.Windowed = true;
    pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    pp.BackBufferFormat = D3DFMT_UNKNOWN;

    if(FAILED(driver->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
                                     p_init->wdgt, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                     &m_logic.present, NULL, &m_logic.device) ))
    {//1
        mLOGERROR("direct x create device");
        return EFAIL;
    }//1


    // Turn off culling, so we see the front and back of the triangle
    m_logic.device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    // Turn off D3D lighting, since we are providing our own vertex colors
    m_logic.device->SetRenderState( D3DRS_LIGHTING, FALSE );
    sRaserDataClear();
    sInitMatrixes();
    if(EDONE != sIBCreate(500))
    {//1
        mLOG_CRITICAL_ERROR("no indexes, no render");
        return EFAIL;
    }//1

    return EDONE;
}
//============================================================================//
void
EC_RENDER::sInitMatrixes()
{
    D3DXMATRIXA16 matWorld;

    D3DXMatrixRotationY( &matWorld, 0 );
    m_logic.device->SetTransform( D3DTS_WORLD, &matWorld );

    D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    m_logic.device->SetTransform( D3DTS_VIEW, &matView );

    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f );
    m_logic.device->SetTransform( D3DTS_PROJECTION, &matProj );
}
//============================================================================//
si32
EC_RENDER::sBufferCreate(ui32 vertex_buffer_size, ui32 vertex_buffer_format, ui32 index_buffer_size)
{
    m_raster.index_buffer_size = index_buffer_size;
    m_raster.vertex_buffer_size = vertex_buffer_size;

    if(FAILED(m_logic.device->CreateVertexBuffer( vertex_buffer_size, 0, vertex_buffer_format, D3DPOOL_DEFAULT, &m_raster.vertex_buffer, NULL ) ))
    {//1
        mLOGERROR("creating vertex buffer");
        return EFAIL;
    }//1
    if(index_buffer_size > 0)
    {//1
        if(FAILED(m_logic.device->CreateIndexBuffer(index_buffer_size, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_raster.index_buffer, NULL)))
        {//2
            mLOGERROR("index creation");
            return EFAIL;
        }//2
    }//1
    return EDONE;
}
//============================================================================//
EC_RENDER::VB*
EC_RENDER::sVBCheck(ui32 format)
{
//    VB* buffer = &m_buffers[format];
//    mLOGTODO("If check out is needed then check it");
    MAP_VB_ITER i = m_buffers.find(format);
    if(i == m_buffers.end())
    {//1
        return NULL;
    }//1
    VB* buffer = &i->second;
    return buffer;
}
//============================================================================//
EC_RENDER::VB*
EC_RENDER::sVBCreate(ui32 format, ui32 total_size)
{
    VB buffer;
    if(FAILED( m_logic.device->CreateVertexBuffer( total_size, 0, format, D3DPOOL_DEFAULT, &buffer.vb, NULL ) ) )
    {//1
        mLOGERROR("creation vertex buffer");
        return NULL;
    }//1
    buffer.vb_format = format;
    buffer.vb_size = total_size;

    m_buffers[format] = buffer;
    mLOGTODO("If check out is needed then check it");
    return &m_buffers[format];
}
//============================================================================//
si32
EC_RENDER::sVBExpand(VB* buffer, ui32 new_size)
{// расширяет буфер вершин
    LPDIRECT3DVERTEXBUFFER9 vertexb;
    if(FAILED( m_logic.device->CreateVertexBuffer( new_size, 0, buffer->vb_format, D3DPOOL_DEFAULT, &vertexb, NULL ) ) )
    {//1
        mLOGERROR("expanding vertex buffer");
        return NULL;
    }//1

    buffer->vb->Release();
    buffer->vb = vertexb;
    buffer->vb_size = new_size;

    return EDONE;
}
//============================================================================//
si32
EC_RENDER::sIBCreate(ui32 index_b_size)
{
    if(FAILED( m_logic.device->CreateIndexBuffer( index_b_size, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_raster.index_buffer, NULL)))
    {//1 нет индексов, нет рисования
        mLOG_CRITICAL_ERROR("failed creation index buffer");
        return EFAIL;
    }//1
    m_raster.index_buffer_size = index_b_size;
    return EDONE;
}
//============================================================================//
si32
EC_RENDER::sIBExpand(ui32 new_size)
{
    LPDIRECT3DINDEXBUFFER9  ib;
    if( FAILED( m_logic.device->CreateIndexBuffer( new_size, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &ib, NULL)))
    {//1 новый буфер не выделился, но старый же есть
        mLOG_CRASH_ERROR("failed expand indexes");
        return EFAIL;
    }//1
    m_raster.index_buffer->Release();
    m_raster.index_buffer = ib;
    m_raster.index_buffer_size = new_size;
    return EDONE;
}
//============================================================================//
si32
EC_RENDER::sRasterFill(VB* p_filler, ES_DRAW_DATA* p_data, ui32 data_size, bool tex, bool col, bool nor)
{// заполняет буффер вершин

mBLOCK("Prepare vertex")
    float* tmp_vertex_data = 0;
    if( FAILED( p_filler->vb->Lock(0, data_size, (void**)&tmp_vertex_data, 0 ) ) )
    {//1
        mLOGERROR("locking filler");
        return EFAIL;
    }//1

mBLOCK("Fill vertexes");
    ui32 pos_step = 3 + ( (col)?1:0 ) + ( (tex)?2:0 ) + ( (nor)?3:0 );
    for(ui32 i = 0; i < p_data->fVertexCountGet(); i ++)
    {//1 copying positions
        ui32 from = i * 3;
        ui32 to = i * pos_step;
        tmp_vertex_data[   to   ] = p_data->positions[   from   ];
        tmp_vertex_data[ to + 1 ] = p_data->positions[ from + 1 ];
        tmp_vertex_data[ to + 2 ] = p_data->positions[ from + 2 ];
    }//1
    if(col)
    {//1
        ui32 col_ofs = 3;
        for(ui32 i = 0; i < p_data->fVertexCountGet(); i++)
        {//2 colors
            ui32 to = i * pos_step + col_ofs;
            (si32&)tmp_vertex_data[ to ] = p_data->colors[i];
        }//2
    }//1

mBLOCK("Finish vertexes");
    p_filler->vb->Unlock();
    m_raster.vertex_buffer  = p_filler->vb;
    m_raster.raster_format  = p_filler->vb_format;
    m_raster.vertex_size    = p_data->fVertexSizeOfGet( tex, col, nor);
    m_raster.total_size     = data_size;
    m_raster.vertex_count   = p_data->fVertexCountGet();

mBLOCK("Prepare index");
    if(p_data->index_count == 0)
    {//1 индексов нет, заполнять нечем
        m_raster.index_count = 0;
        m_raster.primitive_count = p_data->fVertexCountGet() / 3;
        return EDONE;
    }//1
    if(m_raster.index_buffer_size < p_data->index_count)
    {//1 имеющегося буфера недостаточно
        if(EDONE != sIBExpand(p_data->index_count + 10))
        {//2 буффер не выделился, этот объект мы не нарисуем
            mLOGERROR(" index buffer to small");
            return EFAIL;
        }//2
    }//1
    m_raster.index_count = p_data->index_count;
    E_RENDER_INDEX_TYPE*  index_data;
    if( FAILED (m_raster.index_buffer->Lock(0, p_data->index_count * sizeof(E_RENDER_INDEX_TYPE), (void**)&index_data, D3DLOCK_DISCARD) ) )
    {//1 серьезная ошибка которую можно не пережить. вершины заполнены, но индексы залочить неудалось. рисоваться нельзя.
        sRaserDataClear();
        mLOG_CRASH_ERROR("locking index buffer");
        return EFAIL;
    }//1
    ui32 index_data_size = p_data->index_count * sizeof(E_RENDER_INDEX_TYPE);
    memcpy(index_data, p_data->indexes, index_data_size);
    m_raster.index_buffer->Unlock();

mBLOCK("Finishing filling indexes");
    m_raster.primitive_count = p_data->index_count / 3;

    return EDONE;
}
//============================================================================//
ui32
EC_RENDER::sRasterFormatGet(bool tex, bool col, bool nor)
{
    ui32 format = D3DFVF_XYZ;
    if(tex)
    {//1
        format |= D3DFVF_TEX0;
    }//1
    if(col)
    {//1
        format |= D3DFVF_DIFFUSE;
    }//1
    if(nor)
    {//1
        format |= D3DFVF_NORMAL;
    }//1
    return format;
}
//============================================================================//
si32
EC_RENDER::fDraw(ES_DRAW_DATA* p_data, ES_DRAW_OPTIONS* p_options)
{
mBLOCK("Check")
    if(NULL == p_data)
    {//1
        mLOGERROR("draw data with no data");
        return EFAIL;
    }//1
    if(NULL == p_data->positions)
    {//1
        mLOGERROR("draw data without positions disabled");
        return EFAIL;
    }//1


    bool    use_col = false;
    bool    use_nor = false;
    bool    use_tex = false;
mBLOCK("Options");
    if(p_options->diffused && NULL != p_data->colors)
    {//1
        use_col = true;
    }//1
    if(p_options->texured && NULL != p_data->texels)
    {//1
        use_tex = true;
    }//1

mBLOCK("Getting vertex buffer");
    ui32 total_size = p_data->fVertexCountGet() * p_data->fVertexSizeOfGet(use_tex, use_col, use_nor);
    ui32 vertex_format = sRasterFormatGet(use_tex, use_col, use_nor);
    VB* buffer = sVBCheck(vertex_format);
    if(NULL == buffer)
    {//1

        buffer = sVBCreate(vertex_format, total_size + 100);
        if(NULL == buffer)
        {//2
            mLOGERROR("cant create vertex buffer");
            return EFAIL;
        }//2
    }//1
    if(buffer->vb_size <= total_size)
    {//1 гарантирует что буфер всегда сможет принять необходимое количество данных
        if(EDONE != sVBExpand(buffer, total_size + 1))
        {//2
            mLOGERROR("expanding buffer");
            return EFAIL;
        }//2
    }//1

mBLOCK("Filling vertex buffer");
    if(EDONE != sRasterFill(buffer, p_data, total_size, use_tex, use_col, use_nor))
    {//1
        mLOGERROR("cant fill raster data");
        return EFAIL;
    }//1

mBLOCK("Drawing data to surface");
return sDrawRasterData();
}
//============================================================================//
si32
EC_RENDER::sDrawRasterData()
{// отрисовать подготовленную информацию
    if(m_raster.primitive_count == 0)
    {//1
        mLOGERROR("raster data empty");
        return EFAIL;
    }//1
    m_logic.device->SetStreamSource( 0, m_raster.vertex_buffer, 0, m_raster.vertex_size );
    m_logic.device->SetIndices(m_raster.index_buffer);
    m_logic.device->SetFVF( m_raster.raster_format );
    if(0 == m_raster.index_count)
    {//1
        m_logic.device->DrawPrimitive( D3DPT_TRIANGLELIST, 0, m_raster.primitive_count );
    }//1
    else
    {//1
        m_logic.device->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, m_raster.vertex_count, 0, m_raster.primitive_count );
    }//1

    return EDONE;
}
//============================================================================//
si32
EC_RENDER::fFrameClear(bool pixels, ui32 color, bool z_order, sf32 zvalue, bool stencil, ui16 svalue)
{
    ui32    choi = 0;
    if(pixels)
        choi |= D3DCLEAR_TARGET;

    if(z_order)
        choi |= D3DCLEAR_ZBUFFER;

    if(stencil)
        choi |= D3DCLEAR_STENCIL;
    if(choi)
        m_logic.device->Clear( 0, NULL, choi, color, zvalue, svalue );
    else
        return EFAIL;

    return EDONE;
}
//============================================================================//
si32
EC_RENDER::fFrameLock()
{
    if( SUCCEEDED( m_logic.device->BeginScene() ) )
        return EDONE;

    mLOGERROR("begin scene");
    return EFAIL;
}
//============================================================================//
si32
EC_RENDER::fFrameUnlock()
{
    m_logic.device->EndScene();
    return EDONE;
}

//============================================================================//
si32
EC_RENDER::fFramePresent()
{
    m_logic.device->Present( NULL, NULL, NULL, NULL );
    return EDONE;
}
//============================================================================//
void
EC_RENDER::sRaserDataClear()
{
    memset( &m_raster, 0, sizeof(RASTER));
}
//============================================================================//






