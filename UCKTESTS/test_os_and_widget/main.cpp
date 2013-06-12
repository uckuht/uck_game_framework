#include "OS/OS.h"
#include "RENDER/RENDER.h"
#include "BASE/ELANG.h"
#include "BASE/EMACRO.h"
#include "RENDER/ES_DRAW_DATA.h"
#include "RENDER/ES_DRAW_OPTIONS.h"
//============================================================================//

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------

//============================================================================//
int
main()
{
    EC_OS       g_os;
    EC_WIDGET   g_wdgt;
    EC_RENDER   g_render;
    mLOG("Starting");
    g_wdgt.fOnInit(L"VSGE");
    g_wdgt.fRectSet(100, 100, 1200, 500);
    g_wdgt.fWdgtCreate(false);
    g_wdgt.fWdgtShow();
    EC_RENDER::INIT_STRUCT ini_str;

    ini_str.wdgt = g_wdgt.fHandlerGet();
    ini_str.bb_size.fClear();

    ES_DRAW_DATA draw_data;
    draw_data.fOnInit( 3,0, false, true);
    draw_data.fVertexPositionSet(0, -1,-1,0);
    draw_data.fVertexPositionSet(1,  1,-1,0);
    draw_data.fVertexPositionSet(2,  0, 1,0);
//    draw_data.fVertexColorSet(0,ECOLOR_RED);
//    draw_data.fVertexColorSet(1,ECOLOR_RED);
//    draw_data.fVertexColorSet(2,ECOLOR_RED);

    ES_DRAW_OPTIONS draw_opt;
    draw_opt.fClear();
    draw_opt.fDiffuseSet(true);

    g_render.fOnInit(&ini_str);
    while(true)
    {//1
        g_os.fOnUpdate();

        g_render.fFrameClear(true, ECOLOR_BLUE,false,0,false ,0);
        if(EDONE == g_render.fFrameLock())
        {//1
            g_render.fDraw(&draw_data, &draw_opt);
            g_render.fFrameUnlock();
        }//1
        g_render.fFramePresent();
    }//1
    return EAPPNOERROR;
}
//============================================================================//

//
//
//
////-----------------------------------------------------------------------------
//// Name: InitD3D()
//// Desc: Initializes Direct3D
////-----------------------------------------------------------------------------
//HRESULT InitD3D( HWND hWnd )
//{
//    // Create the D3D object.
//    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
//        return E_FAIL;
//
//    // Set up the structure used to create the D3DDevice
//    D3DPRESENT_PARAMETERS d3dpp;
//    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
//    d3dpp.Windowed = TRUE;
//    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
//    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
//
//    // Create the D3DDevice
//    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
//                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
//                                      &d3dpp, &g_pd3dDevice ) ) )
//    {
//        return E_FAIL;
//    }
//
//    return S_OK;
//}
//
//
//
//
////-----------------------------------------------------------------------------
//// Name: InitVB()
//// Desc: Creates a vertex buffer and fills it with our vertices. The vertex
////       buffer is basically just a chuck of memory that holds vertices. After
////       creating it, we must Lock()/Unlock() it to fill it. For indices, D3D
////       also uses index buffers. The special thing about vertex and index
////       buffers is that they can be created in device memory, allowing some
////       cards to process them in hardware, resulting in a dramatic
////       performance gain.
////-----------------------------------------------------------------------------
//HRESULT InitVB()
//{
//    // Initialize three vertices for rendering a triangle
//    CUSTOMVERTEX vertices[] =
//    {
//        { 150.0f,  50.0f, 0.5f, 1.0f, 0xffff0000, }, // x, y, z, rhw, color
//        { 250.0f, 250.0f, 0.5f, 1.0f, 0xff00ff00, },
//        {  50.0f, 250.0f, 0.5f, 1.0f, 0xff00ffff, },
//    };
//
//    // Create the vertex buffer. Here we are allocating enough memory
//    // (from the default pool) to hold all our 3 custom vertices. We also
//    // specify the FVF, so the vertex buffer knows what data it contains.
//    if( FAILED( g_pd3dDevice->CreateVertexBuffer( 3 * sizeof( CUSTOMVERTEX ),
//                                                  0, D3DFVF_CUSTOMVERTEX,
//                                                  D3DPOOL_DEFAULT, &g_pVB, NULL ) ) )
//    {
//        return E_FAIL;
//    }
//
//    // Now we fill the vertex buffer. To do this, we need to Lock() the VB to
//    // gain access to the vertices. This mechanism is required becuase vertex
//    // buffers may be in device memory.
//    VOID* pVertices;
//    if( FAILED( g_pVB->Lock( 0, sizeof( vertices ), ( void** )&pVertices, 0 ) ) )
//        return E_FAIL;
//    memcpy( pVertices, vertices, sizeof( vertices ) );
//    g_pVB->Unlock();
//
//    return S_OK;
//}
//
//
//
//
////-----------------------------------------------------------------------------
//// Name: Cleanup()
//// Desc: Releases all previously initialized objects
////-----------------------------------------------------------------------------
//VOID Cleanup()
//{
//    if( g_pVB != NULL )
//        g_pVB->Release();
//
//    if( g_pd3dDevice != NULL )
//        g_pd3dDevice->Release();
//
//    if( g_pD3D != NULL )
//        g_pD3D->Release();
//}
//
//
//
//
////-----------------------------------------------------------------------------
//// Name: Render()
//// Desc: Draws the scene
////-----------------------------------------------------------------------------
//VOID Render()
//{
//    // Clear the backbuffer to a blue color
//    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0f, 0 );
//
//    // Begin the scene
//    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
//    {
//        // Draw the triangles in the vertex buffer. This is broken into a few
//        // steps. We are passing the vertices down a "stream", so first we need
//        // to specify the source of that stream, which is our vertex buffer. Then
//        // we need to let D3D know what vertex shader to use. Full, custom vertex
//        // shaders are an advanced topic, but in most cases the vertex shader is
//        // just the FVF, so that D3D knows what type of vertices we are dealing
//        // with. Finally, we call DrawPrimitive() which does the actual rendering
//        // of our geometry (in this case, just one triangle).
//        g_pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof( CUSTOMVERTEX ) );
//        g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
//        g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 1 );
//
//        // End the scene
//        g_pd3dDevice->EndScene();
//    }
//
//    // Present the backbuffer contents to the display
//    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
//}
//
//
//
//
////-----------------------------------------------------------------------------
//// Name: MsgProc()
//// Desc: The window's message handler
////-----------------------------------------------------------------------------
//LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
//{
//    switch( msg )
//    {
//        case WM_DESTROY:
//            Cleanup();
//            PostQuitMessage( 0 );
//            return 0;
//    }
//
//    return DefWindowProc( hWnd, msg, wParam, lParam );
//}
//
//
//
//
////-----------------------------------------------------------------------------
//// Name: wWinMain()
//// Desc: The application's entry point
////-----------------------------------------------------------------------------
////INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
//int main()
//{
//
//    // Register the window class
//    WNDCLASSEXW wc =
//    {
//        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
//        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
//        L"D3D Tutorial", NULL
//    };
//    RegisterClassExW( &wc );
//
//    // Create the application's window
//    HWND hWnd = CreateWindowW( L"D3D Tutorial", L"D3D Tutorial 02: Vertices",
//                              WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
//                              NULL, NULL, wc.hInstance, NULL );
//
//    // Initialize Direct3D
//    if( SUCCEEDED( InitD3D( hWnd ) ) )
//    {
//        // Create the vertex buffer
//        if( SUCCEEDED( InitVB() ) )
//        {
//            // Show the window
//            ShowWindow( hWnd, SW_SHOWDEFAULT );
//            UpdateWindow( hWnd );
//
//            // Enter the message loop
//            MSG msg;
//            ZeroMemory( &msg, sizeof( msg ) );
//            while( msg.message != WM_QUIT )
//            {
//                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
//                {
//                    TranslateMessage( &msg );
//                    DispatchMessage( &msg );
//                }
//                else
//                    Render();
//            }
//        }
//    }
//
//    UnregisterClassW( L"D3D Tutorial", wc.hInstance );
//    return 0;
//}
