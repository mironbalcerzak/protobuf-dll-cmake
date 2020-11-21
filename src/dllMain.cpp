#include <stdio.h>
extern "C"
{
    __declspec(dllexport) void hello()
    {
        printf ("Hello DLL.\n");
    }
}