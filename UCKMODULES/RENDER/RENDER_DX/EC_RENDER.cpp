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
si32 EC_RENDER::fOnInit(INIT_STRUCT* p_init)
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
EC_RENDER::fDraw(ES_DRAW_DATA* p_data, ES_DRAW_OPTIONS* p_options)
{
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

mBLOCK("Modern")
    {//1
        if(NULL == m_raster.vertex_buffer)
        {//2
            bool    col_use = false;
            bool    tex_use = false;
            bool    nor_use = false;

            m_raster.raster_format = D3DFVF_XYZ;

            if(p_options->diffused && p_data->colors != NULL)
            {//3 color used
                m_raster.raster_format |= D3DFVF_DIFFUSE;
                col_use = true;
            }//3
            m_raster.total_size = p_data->fVertexCountGet() * p_data->fVertexSizeOfGet(tex_use,col_use,nor_use);

            if(FAILED(m_logic.device->CreateVertexBuffer( m_raster.total_size, 0, m_raster.raster_format, D3DPOOL_DEFAULT, &m_raster.vertex_buffer, NULL )))
            {//3 vertex buffer creation failed
                mLOGERROR("creating vertex buffer");
                return EFAIL;
            }//3
            float* p_vertex_buffer_temp_data;
            if( FAILED( m_raster.vertex_buffer->Lock( 0, m_raster.total_size, ( void** )&p_vertex_buffer_temp_data, 0 ) ) )
                return EFAIL;

            //memcpy( p_vertex_buffer_temp_data, /*g_Vertices*/ p_data->positions, m_raster.total_size);
            ui32 pos_step = 3 + ( (col_use)?1:0 ) + ( (tex_use)?2:0 ) + ( (nor_use)?3:0 );
            for(ui32 i = 0; i < p_data->fVertexCountGet(); i ++)
            {//3 copying positions
                ui32 from = i * 3;
                ui32 to = i * pos_step;
                p_vertex_buffer_temp_data[  from  ] = p_data->positions[   from   ];
                p_vertex_buffer_temp_data[from + 1] = p_data->positions[ from + 1 ];
                p_vertex_buffer_temp_data[from + 2] = p_data->positions[ from + 2 ];
            }//3
            if(col_use)
            {//3
                ui32 col_ofs = p_data->fVertexCountGet() * 3;
                for(ui32 i = 0; i < p_data->fVertexCountGet(); i++)
                {//3 colors
                    ui32 to = i + col_ofs;
                    ((si32&)p_vertex_buffer_temp_data[to]) = p_data->colors[i];
                }//3
            }//3
            m_raster.vertex_buffer->Unlock();

            if(NULL != p_data->indexes)
            {//3
                 if(FAILED(m_logic.device->CreateIndexBuffer(p_data->index_count,0,D3DFMT_INDEX16,D3DPOOL_DEFAULT,&m_raster.index_buffer, NULL)))
                 {//4
                     mLOGERROR("index creation");
                     return EFAIL;
                 }//4        if(SUCCEEDED(_pIndexBuffer->Lock(_ibOffset * sizeof(JINDEX_TYPE), countIndex*sizeof(JINDEX_TYPE), (void**)&tmpIndexData, _ibOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD)))
                 ui16*  index_data;
                 m_raster.index_buffer->Lock(0,p_data->index_count*sizeof(ui16),(void**)&index_data,D3DLOCK_DISCARD);
                 memcpy(index_data,p_data->indexes,p_data->index_count*sizeof(ui16));
                 m_raster.index_buffer->Unlock();
            }//3
            m_raster.primitive_count = 2;
            m_raster.vertex_size = p_data->fVertexSizeOfGet(tex_use,col_use,nor_use);
            m_raster.vertex_count = p_data->vertex_count;
        }//2
        sDrawRasterData();
    }//1
    return EDONE;
}
//============================================================================//
si32
EC_RENDER::sDrawRasterData()
{// отрисовать подготовленную информацию
    m_logic.device->SetStreamSource( 0, m_raster.vertex_buffer, 0, m_raster.vertex_size );
    m_logic.device->SetIndices(m_raster.index_buffer);
    m_logic.device->SetFVF( m_raster.raster_format );
    if(NULL == m_raster.index_buffer)
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






