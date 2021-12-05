#include "AWindowsPlatform.h"

extern int main(int argc, char **argv);

extern "C"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR argv, int console)
{
    applicationInstance = hInstance;
    applicationPrevInstance = hPrevInstance;
    arguments = argv;
    consoleVisible = console;

    return main(0, nullptr);
}
