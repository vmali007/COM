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

//{efa6ae4b-c2c7-4bc8-87f8-4550ed0a940e}
const CLSID CLSID_SumSubtract = {0xefa6ae4b, 0xc2c7, 0x4bc8, 0x87, 0xf8, 0x45, 0x50, 0xed, 0x0a, 0x94, 0x0e};

//{64684f41-dd42-4750-ada8-fb2488d742c8}
const IID IID_ISum = {0x64684f41, 0xdd42, 0x4750, 0xad, 0xa8, 0xfb, 0x24, 0x88, 0xd7, 0x42, 0xc8};

//{0d47d8c9-e993-4142-ada2-7e1c1a726812}
const IID IID_ISubtract = {0x0d47d8c9, 0xe993, 0x4142, 0xad, 0xa2, 0x7e, 0x1c, 0x1a, 0x72, 0x68, 0x12};

