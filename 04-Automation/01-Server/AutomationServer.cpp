#include<windows.h>
#include<stdio.h>
#include"AutomationServer.h"

class CMyMath : public IMyMath {
private:
	long m_cRef;
	ITypeInfo *m_pITypeInfo;
public:
	//contructor
	CMyMath(void);
	//distructor
	~CMyMath(void);
	
	//IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall GetTypeInfoCount(UINT*);
	HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo**);
	HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*);
	HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);

	//ISum methods
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	//ISubtract methods
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

	HRESULT InitInstance(void);
};

//class factory class
class CMyMathClassFactory :public IClassFactory {
private:
	long m_cRef;
public:
	//contractor
	CMyMathClassFactory(void);
	//distructor
	~CMyMathClassFactory(void);

	//IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassFactory methods
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
	
};

//global parameters
long glNumberOfActiveComponent = 0;
long glNumberOfServerLocks = 0;

//{055ec1fe-c0ec-4827-b673-10af302ab476}
const GUID LIBID_AutomationServer = { 0x055ec1fe, 0xc0ec, 0x4827, 0xb6, 0x73, 0x10, 0xaf, 0x30, 0x2a, 0xb4, 0x76 };

//DLL main
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
	//code
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}
	return (TRUE);
}

//CSumSubtract implementation
//contructor
CMyMath::CMyMath(void) {
	//code
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponent);
	m_pITypeInfo = NULL;
}

CMyMath::~CMyMath(void) {
	InterlockedDecrement(&glNumberOfActiveComponent);
	
	if (m_pITypeInfo) {
		m_pITypeInfo->Release();
		m_pITypeInfo = NULL;
	}
}

//IUnkown method Implemnetation
HRESULT CMyMath::QueryInterface(REFIID riid, void** ppv) {
	//code
	if (riid == IID_IUnknown) {
		*ppv = static_cast<IMyMath*>(this);
	}
	else if (riid == IID_IDispatch) {
		*ppv = static_cast<IMyMath*>(this);
	}
	else if (riid == IID_IMyMath) {
		*ppv = static_cast<IMyMath*>(this);
	}
	else {
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}

ULONG CMyMath::AddRef(void) {
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMyMath::Release(void) {
	//code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return 0;
	}
	return m_cRef;
}

//IDispatch methods
HRESULT CMyMath::GetTypeInfoCount(UINT* pCountTypeInfo)
{
	*pCountTypeInfo = 1;
	return S_OK;
}

HRESULT CMyMath::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo** ppITypeInfo) 
{
	*ppITypeInfo = NULL;

	if (iTypeInfo != 0)
		return DISP_E_BADINDEX;

	m_pITypeInfo->AddRef();

	*ppITypeInfo = m_pITypeInfo;

	return S_OK;
}

HRESULT CMyMath::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId) 
{
	return DispGetIDsOfNames(m_pITypeInfo, rgszNames, cNames, rgDispId);
}

HRESULT CMyMath::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr)
{
	HRESULT hr;

	hr = DispInvoke(this,
		m_pITypeInfo,
		dispIdMember,
		wFlags,
		pDispParams,
		pVarResult,
		pExcepInfo,
		puArgErr
	);
	
	return hr;

}

//ISum Impleamentation
HRESULT CMyMath::SumOfTwoIntegers(int num1, int num2, int* pSum) {
	//code
	*pSum = num1 + num2;
	return S_OK;
}
	
HRESULT CMyMath::SubtractionOfTwoIntegers(int num1, int num2, int* pSub) {
	//code
	*pSub = num1 - num2;
	return S_OK;
}

HRESULT CMyMath::InitInstance(void)
{
	void ComErrorDescriptionString(HWND, HRESULT);

	HRESULT hr;
	ITypeLib* pITypeLib = NULL;
	
	if (m_pITypeInfo == NULL)
	{
		hr = LoadRegTypeLib(LIBID_AutomationServer,
			1, 0,
			0x00,
			&pITypeLib);

		if (FAILED(hr)) {
			ComErrorDescriptionString(NULL, hr);
			return hr;
		}

		hr = pITypeLib->GetTypeInfoOfGuid(IID_IMyMath, &m_pITypeInfo);

		if (FAILED(hr)) {
			ComErrorDescriptionString(NULL, hr);
			pITypeLib->Release();
			return hr;
		}
		pITypeLib->Release();
	}
	return S_OK;
}

//CSumSubtractClassFactory implementation
//contructure

CMyMathClassFactory::CMyMathClassFactory(void) {
	//code
	m_cRef = 1;
}

//destructor
CMyMathClassFactory::~CMyMathClassFactory(void) {
	//code
}

//IUnknown methods
HRESULT CMyMathClassFactory::QueryInterface(REFIID riid, void** ppv) {
	//code
	if (riid == IID_IUnknown) {
		*ppv = static_cast<IClassFactory*>(this);
	}
	else if (riid == IID_IClassFactory) {
		*ppv = static_cast<IClassFactory*>(this);
	}
	else {
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	
	return S_OK;
}

ULONG CMyMathClassFactory::AddRef(void) {
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMyMathClassFactory::Release(void) {
	//code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return 0;
	}
	return m_cRef;
}

//IClassFactory methods implementation
HRESULT CMyMathClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv) {
	//variable declaration
	CMyMath* pCMyMath = NULL;
	HRESULT hr;
	//code
	if (pUnkOuter != NULL){
		return CLASS_E_NOAGGREGATION;
	}
	pCMyMath = new CMyMath;
	if (pCMyMath == NULL) {
		return E_OUTOFMEMORY;
	}

	pCMyMath->InitInstance();

	hr = pCMyMath->QueryInterface(riid,ppv);

	pCMyMath->Release();
	
	return hr;
}

HRESULT CMyMathClassFactory::LockServer(BOOL fLock) {
	//code
	if (fLock) {
		InterlockedIncrement(&glNumberOfServerLocks);
	}
	else {
		InterlockedDecrement(&glNumberOfServerLocks);
	}
	return S_OK;
}

//Export table COM ddl methods

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv) {
	//variable declaration
	CMyMathClassFactory* pCMyMathClassFactory = NULL;
	HRESULT hr;
	if (rclsid != CLSID_MyMath) {
		return CLASS_E_CLASSNOTAVAILABLE;
	}
	pCMyMathClassFactory = new CMyMathClassFactory;
	if (pCMyMathClassFactory == NULL) {
		return E_OUTOFMEMORY;
	}

	hr = pCMyMathClassFactory->QueryInterface(riid,ppv);
	pCMyMathClassFactory->Release();
	return hr;
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void) {
	//code
	if ((glNumberOfActiveComponent == 0) && (glNumberOfServerLocks == 0)) {
		return S_OK;
	}
	else {
		return S_FALSE;
	}
}

void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	TCHAR* szErrorMessage = NULL;
	TCHAR str[255];

	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&szErrorMessage, 0, NULL) != 0)
	{
		swprintf_s(str, TEXT("%#X : %s"), hr, szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
		swprintf_s(str, TEXT("Could not find description for the Error"));

	MessageBox(hwnd, str, TEXT("COM Error"), MB_OK);
}


//link.exe AutomationServer.obj /DLL /DEF:AutomationServer.def User32.lib Ole32.lib Oleaut32.lib /SUBSYSTEM:WINDOWS
//for proxistub cl.exe /c /EHsc /D REGISTER_PROXY_DLL AutomationProxiStub.c AutomationProxiStubData.c AutomationProxiStubGuids.c
//link.exe AutomationProxiStub.obj AutomationProxiStubGuids.obj AutomationProxiStubData.obj /DLL /DEF:AutomationProxiStub.def /OUT:temp.dll ole32.lib oleaut32.lib advapi32.lib rpcns4.lib rpcrt4.lib /SUBSYSTEM:WINDOWS
//link.exe AutomationProxiStub.obj AutomationProxiStubGuids.obj AutomationProxiStubData.obj /DLL /DEF:AutomationProxiStub.def ole32.lib oleaut32.lib advapi32.lib rpcns4.lib rpcrt4.lib /SUBSYSTEM:WINDOWS

