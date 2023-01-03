#include<windows.h>
#include"ContainmentInnerComponentWithRegFile.h"

//co-class
class CMultiplicationDivision : public IMultiplication, IDivision {
private:
	long m_cRef;
public:
	//contructor
	CMultiplicationDivision(void);
	//distructor
	~CMultiplicationDivision(void);
	
	//IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//ISum methods
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);
	//ISubtract methods
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
};

//class factory class
class CMultiplicationDivisionClassFactory :public IClassFactory {
private:
	long m_cRef;
public:
	//contractor
	CMultiplicationDivisionClassFactory(void);
	//distructor
	~CMultiplicationDivisionClassFactory(void);

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
CMultiplicationDivision::CMultiplicationDivision(void) {
	//code
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponent);
}

CMultiplicationDivision::~CMultiplicationDivision(void) {
	InterlockedDecrement(&glNumberOfActiveComponent);
}

//IUnkown method Implemnetation
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void** ppv) {
	//code
	if (riid == IID_IUnknown) {
		*ppv = static_cast<IMultiplication*>(this);
	}
	else if (riid == IID_IMultiplication) {
		*ppv = static_cast<IMultiplication*>(this);
	}
	else if (riid == IID_IDivision) {
		*ppv = static_cast<IDivision*>(this);
	}
	else {
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}

ULONG CMultiplicationDivision::AddRef(void) {
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMultiplicationDivision::Release(void) {
	//code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete (this);
		return 0;
	}
	return m_cRef;
}

//ISum Impleamentation
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int* pMul) {
	//code
	*pMul = num1 * num2;
	return S_OK;
}
	
HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int* pDiv) {
	//code
	*pDiv = num1 / num2;
	return S_OK;
}

//CSumSubtractClassFactory implementation
//contructure
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void) {
	//code
	m_cRef = 1;
}

//destructor
CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void) {
	//code
}

//IUnknown methods
HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void** ppv) {
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

ULONG CMultiplicationDivisionClassFactory::AddRef(void) {
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMultiplicationDivisionClassFactory::Release(void) {
	//code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return 0;
	}
	return m_cRef;
}

//IClassFactory methods implementation
HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv) {
	//variable declaration
	CMultiplicationDivision* pCMultiplicationDivision = NULL;
	HRESULT hr;
	//code
	if (pUnkOuter != NULL) {
		return CLASS_E_NOAGGREGATION;
	}
	pCMultiplicationDivision = new CMultiplicationDivision;
	if (pCMultiplicationDivision == NULL) {
		return E_OUTOFMEMORY;
	}
	hr = pCMultiplicationDivision->QueryInterface(riid,ppv);

	pCMultiplicationDivision->Release();
	
	return hr;
}

HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock) {
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
	CMultiplicationDivisionClassFactory* pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;
	if (rclsid != CLSID_MultiplicationDivision) {
		return CLASS_E_CLASSNOTAVAILABLE;
	}
	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;
	if (pCMultiplicationDivisionClassFactory == NULL) {
		return E_OUTOFMEMORY;
	}

	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid,ppv);
	pCMultiplicationDivisionClassFactory->Release();
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

//link.exe ContainmentInnerComponentWithRegFile.obj /DLL /DEF:ContainmentInnerComponentWithRegFile.def User32.lib Ole32.lib Oleaut32.lib /SUBSYSTEM:WINDOWS
