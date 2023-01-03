#pragma once
class IMyMath :public IDispatch {
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;

	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;

};

//{dae2328f-b2f7-4879-a58f-f1b2add5f65d}
const CLSID CLSID_MyMath = {0xdae2328f, 0xb2f7, 0x4879, 0xa5, 0x8f, 0xf1, 0xb2, 0xad, 0xd5, 0xf6, 0x5d };

//{2b333038-973b-4e41-b540-08769ea53d12}
const IID IID_IMyMath = {0x2b333038, 0x973b, 0x4e41, 0xb5, 0x40, 0x08, 0x76, 0x9e, 0xa5, 0x3d, 0x12 };

