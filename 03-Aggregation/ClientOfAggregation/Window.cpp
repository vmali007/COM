//header files
#include<windows.h>
#include "Window.h"
#include"Aggragation.h"

//global functions declarations
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//global variable declarations
ISum* pISum = NULL;
ISubtract* pISubtract = NULL;
IMultiplication* pIMultiplication = NULL;
IDivision* pIDivision = NULL;
//Entry point function
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int iCmdShow)
{
    //local variable declarations
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szAppName[]=TEXT("WINDEV");
    HRESULT hr;

    //code
    //COM Library Initialization
    hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        MessageBox(NULL, TEXT("COM Initialization Failed"), TEXT("ERROR"), MB_OK);
        exit(0);
    }

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
    //COM UnInitialization
    CoUninitialize();
    return((int) msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
    //variable Declaration
    HRESULT hr;
    int n1, n2, sum, subtract, multiplication, division;
    TCHAR str[255];

    switch (iMsg)
    {
    case WM_CREATE:
        hr = CoCreateInstance(CLSID_MultiplicationDivision, NULL, CLSCTX_INPROC_SERVER, IID_IMultiplication, (void**)&pIMultiplication);
        if (FAILED(hr)) {
            MessageBox(hwnd, TEXT("IMultiplication Can not be obtained"), TEXT("ERROR"), MB_OK);
            DestroyWindow(hwnd);
        }
        n1 = 55;
        n2 = 45;
        pIMultiplication->MultiplicationOfTwoIntegers(n1, n2, &multiplication);
        wsprintf(str, TEXT("Multiplication of %d and %d is %d"), n1, n2, multiplication);
        MessageBox(hwnd, str, TEXT("subtract"), MB_OK);

        /*
        hr = pIMultiplication->QueryInterface(IID_ISubtract, (void**)&pISubtract);

        if (FAILED(hr)) {
            MessageBox(hwnd, TEXT("ISubtract Can not be obtained"), TEXT("ERROR"), MB_OK);
            DestroyWindow(hwnd);
        }
        
        pISubtract->SubtractionOfTwoIntegers(n1, n2, &subtract);
        wsprintf(str, TEXT("Subtraction of %d and %d is %d"), n1, n2, subtract);
        MessageBox(hwnd, str, TEXT("subtract"), MB_OK);

        hr = pISubtract->QueryInterface(IID_ISum, (void**)&pISum);
        if (FAILED(hr)) {
            MessageBox(hwnd, TEXT("ISUM Can not be obtained"), TEXT("ERROR"), MB_OK);
            DestroyWindow(hwnd);
        }

        pISum->SumOfTwoIntegers(n1, n2, &sum);
        wsprintf(str, TEXT("SUM of %d and %d is %d"), n1, n2, sum);
        MessageBox(hwnd, str, TEXT("SUM"), MB_OK);
        */
        hr = pIMultiplication->QueryInterface(IID_IDivision, (void**)&pIDivision);

        if (FAILED(hr)) {
            MessageBox(hwnd, TEXT("IDivision Can not be obtained"), TEXT("ERROR"), MB_OK);
            DestroyWindow(hwnd);
        }

        pIDivision->DivisionOfTwoIntegers(n1, n2, &division);
        wsprintf(str, TEXT("Division of %d and %d is %d"), n1, n2, division);
        MessageBox(hwnd, str, TEXT("subtract"), MB_OK);

        //safe release
        if (pIDivision) {
            pIDivision->Release();
            pIDivision = NULL;
        }
        if (pISum) {
            pISum->Release();
            pISum = NULL;
        }
        if (pISubtract) {
            pISubtract->Release();
            pISubtract = NULL;
        }
        if (pIMultiplication) {
            pIMultiplication->Release();
            pIMultiplication = NULL;
        }
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        //PostQuitMessage(0);
        PostMessage(hwnd,WM_QUIT,0,0L);
        break;   
    default:
        break;
    }

    return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}



//cl.exe /c /EHsc Window.cpp
//rc.exe Window.rc
//link.exe Window.obj Window.res User32.lib GDI32.lib ole32.lib oleaut32.lib /SUBSYSTEM:WINDOWS
