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
#include "InputHandler.h"

#include "CubeSlideComponent.h"
#include "CubeControlComponent.h"
#include "CubeJumpComponent.h"

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
    InputHandler* inputHandler = new InputHandler();

    GameObject* cubes[100] = {};
    ObjectComponent* component = nullptr;
    srand(time(0));

    for (int i = 0; i < 100; ++i) {
      cubes[i] = new CubeGameObject();
      renderThread->EnqueueCommand(RC_CreateCubeRenderObject, cubes[i]->GetRenderProxy());

      cubes[i]->SetPosition(-15 + 3 * (i % 10), -15, -3 + 3 * (i / 10));
      switch (rand() % 3)
      {
      case 0:
        component = new CubeControlComponent(cubes[i], inputHandler);
        break;

      case 1:
        component = new CubeJumpComponent(cubes[i]);
        break;

      case 2:
        component = new CubeSlideComponent(cubes[i]);
        break;
      }

      cubes[i]->SetComponent(component);
    }

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();

    float newPositionX = 0.0f;

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
            inputHandler->Update();

            float t = 0;
            timer.Tick();
            float elapsedTime = timer.DeltaTime();

            for (int i = 0; i < 100; ++i) {
              cubes[i]->GetComponent()->Update(elapsedTime);
            }

            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}
