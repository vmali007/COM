#pragma once

#undef INTERFACE
#define INTERFACE ISum
DECLARE_INTERFACE_(ISum, IUnknown) {
	//Iunknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID, void**) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	//ISum methods
	STDMETHOD(SumOfTwoIntegers)(THIS_ int, int, int*) PURE;
};

#undef INTERFACE
#define INTERFACE ISubtract
DECLARE_INTERFACE_(ISubtract, IUnknown) {
	//Iunknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID, void**) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	//ISum methods
	STDMETHOD(SubtractionOfTwoIntegers)(THIS_ int, int, int*) PURE;
};

//"{0xbb7d9fb3,0x3751,0x4d53,0xb7,0x3a,0xe1,0x34,0x2f,0x2b,0x89,0x6e}"
const CLSID CLSID_SumSubtract = {0xbb7d9fb3, 0x3751, 0x4d53, 0xb7, 0x3a, 0xe1, 0x34, 0x2f, 0x2b, 0x89, 0x6e};

//"{522f2e94-aad0-4477-90b4-2881ee3a5fd5}"
const IID IID_ISum = {0x522f2e94, 0xaad0, 0x4477, 0x90, 0xb4, 0x28, 0x81, 0xee, 0x3a, 0x5f, 0xd5 };

//{7ab6dd80-46ee-4699-a6fa-43b37d418a14}
const IID IID_ISubtract = {0x7ab6dd80, 0x46ee, 0x4699, 0xa6, 0xfa, 0x43, 0xb3, 0x7d, 0x41, 0x8a, 0x14 };

