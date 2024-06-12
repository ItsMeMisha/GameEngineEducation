// GameEngine.cpp : Defines the entry point for the application.
//

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "GameEngine.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "CubeGameObject.h"
#include "GameTimer.h"

#include "KeyLayout.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // Enable run-time memory check for debug builds.
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    GameTimer timer;

    RenderEngine* renderEngine = new RenderEngine(hInstance);
    RenderThread* renderThread = renderEngine->GetRT();

    GameObject* cube = new CubeGameObject();
    renderThread->EnqueueCommand(RC_CreateCubeRenderObject, cube->GetRenderProxy());

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();

    float cubePositionX = 0.0f;
    float cubePositionZ = 0.0f;
    float deltaPosition = 5.f;

    KeyLayout keyLayout;
    keyLayout.ParseConfig();

    // Main message loop:
    while (msg.message != (WM_QUIT | WM_CLOSE))
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            float t = 0;
            float modifierX = 0.f;
            float modifierZ = 0.f;
            timer.Tick();

            //Check if keys are pressed now
            if (GetAsyncKeyState(keyLayout.GetKey(RIGHT)) & (1 << 15)) {
              modifierX = 1.f;
            } else if (GetAsyncKeyState(keyLayout.GetKey(LEFT)) & (1 << 15)) {
              modifierX = -1.f;
            }

            if (GetAsyncKeyState(keyLayout.GetKey(UP)) & (1 << 15)) {
              modifierZ = 1.f;
            }
            else if (GetAsyncKeyState(keyLayout.GetKey(DOWN)) & (1 << 15)) {
              modifierZ = -1.f;
            }

            cubePositionX += deltaPosition * timer.DeltaTime() * modifierX;
            cubePositionZ += deltaPosition * timer.DeltaTime() * modifierZ;
            cube->SetPosition(cubePositionX, 0.0f, cubePositionZ);

            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}
