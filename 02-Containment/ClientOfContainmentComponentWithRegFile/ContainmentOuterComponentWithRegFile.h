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

//{efa6ae4b-c2c7-4bc8-87f8-4550ed0a940e}
const CLSID CLSID_SumSubtract = {0xefa6ae4b, 0xc2c7, 0x4bc8, 0x87, 0xf8, 0x45, 0x50, 0xed, 0x0a, 0x94, 0x0e};

//{64684f41-dd42-4750-ada8-fb2488d742c8}
const IID IID_ISum = {0x64684f41, 0xdd42, 0x4750, 0xad, 0xa8, 0xfb, 0x24, 0x88, 0xd7, 0x42, 0xc8};

//{0d47d8c9-e993-4142-ada2-7e1c1a726812}
const IID IID_ISubtract = {0x0d47d8c9, 0xe993, 0x4142, 0xad, 0xa2, 0x7e, 0x1c, 0x1a, 0x72, 0x68, 0x12};

//{6829785d-cbd0-4023-b371-948925143218}
const IID IID_IMultiplication = { 0x6829785d, 0xcbd0, 0x4023, 0xb3, 0x71, 0x94, 0x89, 0x25, 0x14, 0x32, 0x18 };

//{fd310291-0ae5-41b9-b69b-fcaba69af194}
const IID IID_IDivision = { 0xfd310291, 0x0ae5, 0x41b9, 0xb6, 0x9b, 0xfc, 0xab, 0xa6, 0x9a, 0xf1, 0x94 };
