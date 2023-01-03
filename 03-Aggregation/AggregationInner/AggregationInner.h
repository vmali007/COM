#pragma once
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

//{58ce4eed-80dc-4eb5-8cf4-98052ddaad01}
const CLSID CLSID_MultiplicationDivision = {0x58ce4eed, 0x80dc, 0x4eb5, 0x8c, 0xf4, 0x98, 0x05, 0x2d, 0xda, 0xad, 0x01};

//{ac6809a3-08ba-43a1-af70-faea3ca81df8}
const IID IID_IMultiplication = {0xac6809a3, 0x08ba, 0x43a1, 0xaf, 0x70, 0xfa, 0xea, 0x3c, 0xa8, 0x1d, 0xf8};

//{07b22ba2-0506-4901-8037-1f3da000482c}
const IID IID_IDivision = {0x07b22ba2, 0x0506, 0x4901, 0x80, 0x37, 0x1f, 0x3d, 0xa0, 0x00, 0x48, 0x2c};

