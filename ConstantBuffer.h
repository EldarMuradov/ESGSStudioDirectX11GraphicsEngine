#pragma once
#include <d3d11.h>

class DeviceContext;

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();
	bool load(void* buffer, UINT size_buffer);
	bool release();
	void update(DeviceContext* device_context, void* buffer);

private:
	ID3D11Buffer* m_buffer;
private:
	friend class DeviceContext;
};



