#include "pch.h"
#include "TW_Direct2D.h"

#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "DWRITE.lib")

// 사용자가 TWD_Core를 재정의해서 사용할 수 있기 때문에
// 사용자는 부모 클래스의 포인터인 TWD_Core* 로 사용을 유도한다.
TWD_Core* gp_tw_d2d;

TWD_Core::TWD_Core()
{
	gp_tw_d2d = this;
	mp_factory = NULL;
	mp_write_factory = NULL;

	// COM을 사용하기 위해 초기화 함수 호출
	if (S_OK == CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)) {
		// D2D 사용을 위한 Factory 생성
		if (S_OK == D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mp_factory)) {
			// 문자열 출력 팩토리
			DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(mp_write_factory),
				reinterpret_cast<IUnknown**>(&mp_write_factory));
		}
	}
}

TWD_Core::~TWD_Core()
{
	if (mp_factory) {
		// D2D 해제
		TWD_IRelease(&mp_write_factory);
		TWD_IRelease(&mp_factory);
	}
	CoUninitialize();
}

ID2D1Factory* TWD_Core::GetFactory()
{
	return mp_factory;
}

IDWriteFactory* TWD_Core::GetWriteFactory()
{
	return mp_write_factory;
}
