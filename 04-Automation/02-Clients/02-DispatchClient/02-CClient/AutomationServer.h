#pragma once

#undef INTERFACE
#define INTERFACE IMyMath
DECLARE_INTERFACE_(IMyMath, IDispatch) {
	//Iunknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID, void**) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	//IDispatch methods
	STDMETHOD(GetTypeInfoCount)(THIS_ UINT*) PURE;
	STDMETHOD(GetTypeInfo)(THIS_ UINT, LCID, ITypeInfo**) PURE;
	STDMETHOD(GetIDsOfNames)(THIS_ REFIID, LPOLESTR*, UINT, LCID, DISPID*) PURE;
	STDMETHOD(Invoke)(THIS_ DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*) PURE;

	//IMyDispatch methods
	STDMETHOD(SumOfTwoIntegers)(THIS_ int, int, int*) PURE;
	STDMETHOD(SubtractionOfTwoIntegers)(THIS_ int, int, int*) PURE;
};

//{dae2328f-b2f7-4879-a58f-f1b2add5f65d}
const CLSID CLSID_IMyMath = {0xdae2328f, 0xb2f7, 0x4879, 0xa5, 0x8f, 0xf1, 0xb2, 0xad, 0xd5, 0xf6, 0x5d };

//{2b333038-973b-4e41-b540-08769ea53d12}
const IID IID_IMyMath = {0x2b333038, 0x973b, 0x4e41, 0xb5, 0x40, 0x08, 0x76, 0x9e, 0xa5, 0x3d, 0x12 };

