#include "pch.h"
#include "TW_Direct2D.h"

#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "DWRITE.lib")

// ����ڰ� TWD_Core�� �������ؼ� ����� �� �ֱ� ������
// ����ڴ� �θ� Ŭ������ �������� TWD_Core* �� ����� �����Ѵ�.
TWD_Core* gp_tw_d2d;

TWD_Core::TWD_Core()
{
	gp_tw_d2d = this;
	mp_factory = NULL;
	mp_write_factory = NULL;

	// COM�� ����ϱ� ���� �ʱ�ȭ �Լ� ȣ��
	if (S_OK == CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)) {
		// D2D ����� ���� Factory ����
		if (S_OK == D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mp_factory)) {
			// ���ڿ� ��� ���丮
			DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(mp_write_factory),
				reinterpret_cast<IUnknown**>(&mp_write_factory));
		}
	}
}

TWD_Core::~TWD_Core()
{
	if (mp_factory) {
		// D2D ����
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
