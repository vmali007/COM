#include<windows.h>
#include"ClassFactoryDllServerWithRageFile.h"

//co-class
class CSumSubtract: public ISum, ISubtract {
private:
	long m_cRef;
public:
	//contructor
	CSumSubtract(void);
	//distructor
	~CSumSubtract(void);
	
	//IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//ISum methods
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	//ISubtract methods
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
};

//class factory class
class CSumSubtractClassFactory :public IClassFactory {
private:
	long m_cRef;
public:
	//contractor
	CSumSubtractClassFactory(void);
	//distructor
	~CSumSubtractClassFactory(void);

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
CSumSubtract::CSumSubtract(void) {
	//code
	long m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponent);
}

CSumSubtract::~CSumSubtract(void) {
	InterlockedDecrement(&glNumberOfActiveComponent);
}

//IUnkown method Implemnetation
HRESULT CSumSubtract::QueryInterface(REFIID riid, void** ppv) {
	//code
	if (riid == IID_IUnknown) {
		*ppv = static_cast<ISum*>(this);
	}
	else if (riid == IID_ISum) {
		*ppv = static_cast<ISum*>(this);
	}
	else if (riid == IID_ISubtract) {
		*ppv = static_cast<ISubtract*>(this);
	}
	else {
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}

ULONG CSumSubtract::AddRef(void) {
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtract::Release(void) {
	//code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete (this);
		return 0;
	}
	return m_cRef;
}

//ISum Impleamentation
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int* pSum) {
	//code
	*pSum = num1 + num2;
	return S_OK;
}
	
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int* pSubtract) {
	//code
	*pSubtract = num1 - num2;
	return S_OK;
}

//CSumSubtractClassFactory implementation
//contructure
CSumSubtractClassFactory::CSumSubtractClassFactory(void) {
	//code
	long m_cRef = 1;
}

//destructor
CSumSubtractClassFactory::~CSumSubtractClassFactory(void) {
	//code
}

//IUnknown methods
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void** ppv) {
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

ULONG CSumSubtractClassFactory::AddRef(void) {
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtractClassFactory::Release(void) {
	//code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return 0;
	}
	return m_cRef;
}

//IClassFactory methods implementation
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv) {
	//variable declaration
	CSumSubtract* pCSumSubtract = NULL;
	HRESULT hr;
	//code
	if (pUnkOuter != NULL) {
		return CLASS_E_NOAGGREGATION;
	}
	pCSumSubtract = new CSumSubtract;
	if (pCSumSubtract == NULL) {
		return E_OUTOFMEMORY;
	}
	hr = pCSumSubtract->QueryInterface(riid,ppv);

	pCSumSubtract->Release();
	
	return hr;
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock) {
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
	CSumSubtractClassFactory* pCSumSubtractClassFactory = NULL;
	HRESULT hr;
	if (rclsid != CLSID_SumSubtract) {
		return CLASS_E_CLASSNOTAVAILABLE;
	}
	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	if (pCSumSubtractClassFactory == NULL) {
		return E_OUTOFMEMORY;
	}

	hr = pCSumSubtractClassFactory->QueryInterface(riid,ppv);
	pCSumSubtractClassFactory->Release();
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

//link.exe ClassFactoryDllServerWithRageFile.obj /DLL /DEF:ClassFactoryDllServerWithRageFile.def User32.lib /SUBSYSTEM:WINDOWS
