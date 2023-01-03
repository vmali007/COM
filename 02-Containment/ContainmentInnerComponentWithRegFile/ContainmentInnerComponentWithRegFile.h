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

//{f3f9bd05-8281-4f71-a359-ef929a52a5d1}
const CLSID CLSID_MultiplicationDivision = {0xf3f9bd05, 0x8281, 0x4f71, 0xa3, 0x59, 0xef, 0x92, 0x9a, 0x52, 0xa5, 0xd1};

//{6829785d-cbd0-4023-b371-948925143218}
const IID IID_IMultiplication = {0x6829785d, 0xcbd0, 0x4023, 0xb3, 0x71, 0x94, 0x89, 0x25, 0x14, 0x32, 0x18};

//{fd310291-0ae5-41b9-b69b-fcaba69af194}
const IID IID_IDivision = {0xfd310291, 0x0ae5, 0x41b9, 0xb6, 0x9b, 0xfc, 0xab, 0xa6, 0x9a, 0xf1, 0x94};

