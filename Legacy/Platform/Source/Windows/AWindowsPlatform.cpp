#include "AWindowsPlatform.h"

#include <Graphics>
#include "AWindowsWindow.h"

HINSTANCE applicationInstance;
HINSTANCE applicationPrevInstance;
LPSTR arguments;
int consoleVisible;
String errorMessage;

ARegisterPlatform(AWindowsPlatform, Windows::OpenGLWindow, AOpenGLGraphicsContext)

AError AWindowsPlatform::main(ARunnable &runnable)
{
    MSG messageHandle = MSG();

    bool running = true;
    while(running)
    {
        runnable.onExecute();

        if (PeekMessage(&messageHandle, nullptr, 0, 0, PM_REMOVE) != 0)
        {
            TranslateMessage(&messageHandle);
            DispatchMessage(&messageHandle);

            if (messageHandle.message == WM_QUIT)
            {
                running = false;
            }
        }

        for (Windows::Window *window : Windows::WindowsManager::getInstance().windows)
        {
            InvalidateRect(window->windowHandle, nullptr, false);
            UpdateWindow(window->windowHandle);
        }
        GraphicsClock.sync();
    }

    UnregisterClass(TEXT("AWindow"), Windows::WindowsManager::getInstance().windowClass.hInstance);

    return AError(messageHandle.wParam, errorMessage);
}

void AWindowsPlatform::stop(const AError &error)
{
    errorMessage = error.getMessage(); //HACK: probably can be desynced with other WM_QUIT messages
    PostQuitMessage(error.getErrorCode());
}
