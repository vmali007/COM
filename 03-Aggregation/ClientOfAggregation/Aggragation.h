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

class IMultiplication :public IUnknown
{
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};
class IDivision :public IUnknown
{
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};

//{073b465b-004c-4939-a5fb-90547a454c30}
const CLSID CLSID_SumSubtract = { 0x073b465b, 0x004c, 0x4939, 0xa5, 0xfb, 0x90, 0x54, 0x7a, 0x45, 0x4c, 0x30};

//{0a4311c1-4734-442b-8806-8e07cae0eb11}
const IID IID_ISum = { 0x0a4311c1, 0x4734, 0x442b, 0x88, 0x06, 0x8e, 0x07, 0xca, 0xe0, 0xeb, 0x11};

//{c91ccfc3-8297-4acc-80db-c27d035d3e6f}
const IID IID_ISubtract = { 0xc91ccfc3, 0x8297, 0x4acc, 0x80, 0xdb, 0xc2, 0x7d, 0x03, 0x5d, 0x3e, 0x6f};

//{58ce4eed-80dc-4eb5-8cf4-98052ddaad01}
const CLSID CLSID_MultiplicationDivision = { 0x58ce4eed, 0x80dc, 0x4eb5, 0x8c, 0xf4, 0x98, 0x05, 0x2d, 0xda, 0xad, 0x01};

//{ac6809a3-08ba-43a1-af70-faea3ca81df8}
const IID IID_IMultiplication = { 0xac6809a3, 0x08ba, 0x43a1, 0xaf, 0x70, 0xfa, 0xea, 0x3c, 0xa8, 0x1d, 0xf8};

//{07b22ba2-0506-4901-8037-1f3da000482c}
const IID IID_IDivision = { 0x07b22ba2, 0x0506, 0x4901, 0x80, 0x37, 0x1f, 0x3d, 0xa0, 0x00, 0x48, 0x2c};
