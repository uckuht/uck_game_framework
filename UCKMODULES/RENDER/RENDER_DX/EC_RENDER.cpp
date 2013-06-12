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
        mLOGERROR("draw data withou positions disabled");
        return EFAIL;
    }//1


mBLOCK("Modern")
    {//1
        if(NULL == m_raster.vertex_buffer)
        {//2
            m_raster.raster_format = D3DFVF_XYZ;
            m_raster.total_size = p_data->fVertexCountGet() * p_data->fVertexSizeOfGet();
            if(FAILED(m_logic.device->CreateVertexBuffer( m_raster.total_size, 0, m_raster.raster_format, D3DPOOL_DEFAULT, &m_raster.vertex_buffer, NULL )))
            {//3
                mLOGERROR("creating vertex buffer");
                return EFAIL;
            }//3
            void* p_vertex_buffer_temp_data;
            if( FAILED( m_raster.vertex_buffer->Lock( 0, m_raster.total_size, ( void** )&p_vertex_buffer_temp_data, 0 ) ) )
                return EFAIL;

            memcpy( p_vertex_buffer_temp_data, /*g_Vertices*/ p_data->positions, m_raster.total_size);
            m_raster.vertex_buffer->Unlock();
            m_raster.primitive_count = 1;
            m_raster.vertex_size = p_data->fVertexSizeOfGet();
        }//2
        sDrawRasterData();
    }//1
mBLOCK("Out dated")
    if(false)
    {//1
        if(NULL == p_vb)
        {//2
            ui32 full_size = p_data->fVertexSizeOfGet() * p_data->fVertexCountGet();
            if( FAILED( m_logic.device->CreateVertexBuffer( full_size, 0, D3DFVF_XYZ, D3DPOOL_DEFAULT, &p_vb, NULL ) ) )
            {
                mLOGERROR("creating vertex buffer");
                return EFAIL;
            }

            void* p_vertex_buffer_temp_data;

            if( FAILED( p_vb->Lock( 0, full_size, ( void** )&p_vertex_buffer_temp_data, 0 ) ) )
                return EFAIL;

            memcpy( p_vertex_buffer_temp_data, /*g_Vertices*/ p_data->positions, full_size);

            p_vb->Unlock();


        }//2
        m_logic.device->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0f, 0 );
        // Begin the scene
        if( SUCCEEDED( m_logic.device->BeginScene() ) )
        {
            // Draw the triangles in the vertex buffer. This is broken into a few
            // steps. We are passing the vertices down a "stream", so first we need
            // to specify the source of that stream, which is our vertex buffer. Then
            // we need to let D3D know what vertex shader to use. Full, custom vertex
            // shaders are an advanced topic, but in most cases the vertex shader is
            // just the FVF, so that D3D knows what type of vertices we are dealing
            // with. Finally, we call DrawPrimitive() which does the actual rendering
            // of our geometry (in this case, just one triangle).
            m_logic.device->SetStreamSource( 0, p_vb, 0, p_data->fVertexSizeOfGet() );
            m_logic.device->SetFVF( D3DFVF_CUSTOMVERTEX );
            m_logic.device->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 1 );

            // End the scene
            m_logic.device->EndScene();
        }

        // Present the backbuffer contents to the display
        m_logic.device->Present( NULL, NULL, NULL, NULL );
    }//1

    return EDONE;
}
//============================================================================//
si32
EC_RENDER::sDrawRasterData()
{// отрисовать подготовленную информацию
    m_logic.device->SetStreamSource( 0, m_raster.vertex_buffer, 0, m_raster.vertex_size );
    m_logic.device->SetFVF( m_raster.raster_format );
    m_logic.device->DrawPrimitive( D3DPT_TRIANGLELIST, 0, m_raster.primitive_count );

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






