//header files
#include<windows.h>
#include "Window.h"
#include "AutomationServer.h"


//global functions declarations
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//global variable declarations

//Entry point function
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int iCmdShow)
{
    //local variable declarations
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szAppName[]=TEXT("WINDEV");

    //code
    //wnd class
    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW|CS_VREDRAW;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.lpfnWndProc = WndProc;
    wndclass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(MYICON));
    wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

    //registraton of WNDCLASS
    RegisterClassEx (&wndclass);

    //creating the window
    hwnd = CreateWindow(szAppName,TEXT("VDM:Window"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);

    //SHOW THE WINDOW
    ShowWindow (hwnd,iCmdShow);

    //Update Wondow
    UpdateWindow(hwnd);

    //massage loop
    while(GetMessage(&msg,NULL,0,0))
    {
        //translate masage
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return((int) msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
    IMyMath* pIMyMath = NULL;
    HRESULT hr;
    int num1, num2,sum,sub;
    TCHAR str[255];

    switch (iMsg)
    {
    case WM_CREATE:
        hr = CoInitialize(NULL);
        if (FAILED(hr)) {
            MessageBox(hwnd, TEXT("CoInitilize Failed"), TEXT("ERROE"), MB_OK);
            DestroyWindow(hwnd);
        }
        hr = CoCreateInstance(CLSID_MyMath, NULL, CLSCTX_INPROC_SERVER, IID_IMyMath, (void**)&pIMyMath);
        if (FAILED(hr)) {
            MessageBox(hwnd, TEXT("CoCreateInstance Failed to get IMyMath interface"), TEXT("ERROE"), MB_OK);
            DestroyWindow(hwnd);
        }
        num1 = 175;
        num2 = 125;
        pIMyMath->SumOfTwoIntegers(num1, num2, &sum);
        wsprintf(str, TEXT("Sum Of %d and %d is %d"), num1, num2, sum);
        MessageBox(hwnd, str, TEXT("SUM"), MB_OK);

        pIMyMath->SubtractionOfTwoIntegers(num1, num2, &sub);
        wsprintf(str, TEXT("Subtraction Of %d and %d is %d"), num1, num2, sub);
        MessageBox(hwnd, str, TEXT("SUBTRACTION"), MB_OK);

        pIMyMath->Release();

        pIMyMath = NULL;
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        CoUninitialize();
        PostQuitMessage(0);
        break;   
    default:
        break;
    }

    return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}



//cl.exe /c /EHsc Window.cpp
//rc.exe Window.rc
//link.exe Window.obj Window.res User32.lib GDI32.lib ole32.lib oleaut32.lib /SUBSYSTEM:WINDOWS
