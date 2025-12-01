#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>

//DirectX基礎
class DirectXCommon
{
public:
	void Initialize();
	void DeviceInitialize();
	void CommondListInitialize();
private:
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;


};