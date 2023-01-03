#pragma once
class ISum :public IUnknown
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubtract :public IUnknown
{
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

//{073b465b-004c-4939-a5fb-90547a454c30}
const CLSID CLSID_SumSubtract = {0x073b465b, 0x004c, 0x4939, 0xa5, 0xfb, 0x90, 0x54, 0x7a, 0x45, 0x4c, 0x30};

//{0a4311c1-4734-442b-8806-8e07cae0eb11}
const IID IID_ISum = {0x0a4311c1, 0x4734, 0x442b, 0x88, 0x06, 0x8e, 0x07, 0xca, 0xe0, 0xeb, 0x11};

//{c91ccfc3-8297-4acc-80db-c27d035d3e6f}
const IID IID_ISubtract = {0xc91ccfc3, 0x8297, 0x4acc, 0x80, 0xdb, 0xc2, 0x7d, 0x03, 0x5d, 0x3e, 0x6f};

