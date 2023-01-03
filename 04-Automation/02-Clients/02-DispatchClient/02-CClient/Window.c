//header files
#include<windows.h>
#include "Window.h"
#include"AutomationServer.h"

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
    HRESULT hr;

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
    IMyMath* pIMyDispatch = NULL;
    HRESULT hr;
    //BSTR binary or basic string
    OLECHAR* szFunctionName1 = L"SumOfTwoIntegers";
    OLECHAR* szFunctionName2 = L"SubtractionOfTwoIntegers";
    VARIANT vArg[2];
    VARIANT vResult;
    DISPID dispid;
    DISPPARAMS params;
    int num1, num2, sum, sub;
    TCHAR str[255];

    switch (iMsg)
    {
    case WM_CREATE:
        hr = CoInitialize(NULL);
        if (FAILED(hr)) {
            MessageBox(hwnd, TEXT("CoInitilize Failed"), TEXT("ERROE"), MB_OK);
            DestroyWindow(hwnd);
        }
        hr = CoCreateInstance(&CLSID_IMyMath, NULL, CLSCTX_INPROC_SERVER, &IID_IDispatch, (void**)&pIMyDispatch);
        if (FAILED(hr)) {
            MessageBox(hwnd, TEXT("CoCreateInstance Failed to get IMyDispatch interface"), TEXT("ERROE"), MB_OK);
            DestroyWindow(hwnd);
        }
        num1 = 275;
        num2 = 225;
        //Get ID of SumOfTwoIntegers()
        hr = pIMyDispatch->lpVtbl->GetIDsOfNames(pIMyDispatch,
            &IID_NULL,
            &szFunctionName1,
            1,
            GetUserDefaultLCID(),
            &dispid);
        if (FAILED(hr)) {
            MessageBox(hwnd, TEXT("GetIDsOfNames Failed to get ID of SumOfTwoIntegers"), TEXT("ERROE"), MB_OK);
            pIMyDispatch->lpVtbl->Release(pIMyDispatch);
            pIMyDispatch = NULL;
            DestroyWindow(hwnd);
        }
        //call SumOfTwoIntegers() by passing its ID to Invoke()
        VariantInit(vArg);
        vArg[0].vt = VT_INT;
        vArg[0].intVal = num2;
        vArg[1].vt = VT_INT;
        vArg[1].intVal = num1;
        VariantInit(&vResult);

        params.rgvarg = vArg;
        params.cArgs = 2;
        params.rgdispidNamedArgs = NULL;
        params.cNamedArgs = 0;

        hr = pIMyDispatch->lpVtbl->Invoke(pIMyDispatch,
            dispid,
            &IID_NULL,
            GetUserDefaultLCID(),
            DISPATCH_METHOD,
            &params,
            &vResult,
            NULL,
            NULL
        );
        sum = vResult.lVal;
        wsprintf(str, TEXT("SUM of %d and %d is %d"), num1, num2, sum);
        MessageBox(hwnd, str, TEXT("SUM"), MB_OK);

        //Get ID of SubtractionOfTwoIntegers()
        hr = pIMyDispatch->lpVtbl->GetIDsOfNames(pIMyDispatch,
            &IID_NULL,
            &szFunctionName2,
            1,
            GetUserDefaultLCID(),
            &dispid);
        if (FAILED(hr)) {
            MessageBox(hwnd, TEXT("GetIDsOfNames Failed to get ID of SubtractionOfTwoIntegers"), TEXT("ERROE"), MB_OK);
            pIMyDispatch->lpVtbl->Release(pIMyDispatch);
            pIMyDispatch = NULL;
            DestroyWindow(hwnd);
        }
        //call SubtractionOfTwoIntegers() by passing its ID to Invoke()
        VariantInit(vArg);
        vArg[0].vt = VT_INT;
        vArg[0].intVal = num2;
        vArg[1].vt = VT_INT;
        vArg[1].intVal = num1;
        VariantInit(&vResult);

        params.rgvarg = vArg;
        params.cArgs = 2;
        params.rgdispidNamedArgs = NULL;
        params.cNamedArgs = 0;

        hr = pIMyDispatch->lpVtbl->Invoke(pIMyDispatch,
            dispid,
            &IID_NULL,
            GetUserDefaultLCID(),
            DISPATCH_METHOD,
            &params,
            &vResult,
            NULL,
            NULL
        );
        sub = vResult.lVal;
        
        wsprintf(str, TEXT("Subtraction of %d and %d is %d"), num1, num2, sub);
        MessageBox(hwnd, str, TEXT("subtract"), MB_OK);

        //safe release
        pIMyDispatch->lpVtbl->Release(pIMyDispatch);
        pIMyDispatch = NULL;
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;   
    default:
        break;
    }

    return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}



//cl.exe /c /EHsc Window.c
//rc.exe Window.rc
//link.exe Window.obj Window.res User32.lib GDI32.lib ole32.lib oleaut32.lib /SUBSYSTEM:WINDOWS
