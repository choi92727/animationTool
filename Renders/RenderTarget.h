#pragma once

class RenderTarget
{
public:
	RenderTarget();
	~RenderTarget();

	ID3D11RenderTargetView* GetRTV()
	{
		return rtv;
	}

	ID3D11ShaderResourceView* GetSRV()
	{
		return srv;
	}

	ID3D11Texture2D* GetTexture()
	{
		return texture;
	}

	UINT GetWidth() { return width; }
	UINT GetHeight() { return height; }

	void Set();

	void Create(UINT width = 0, UINT height = 0);

private:
	void Delete();

private:
	UINT width, height;

	ID3D11Texture2D* texture;
	ID3D11RenderTargetView* rtv;
	ID3D11ShaderResourceView* srv;
};