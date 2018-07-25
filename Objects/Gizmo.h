#pragma once

class BoundingFrustum;

namespace Gizmo
{
	class Gizmo
	{
	public:
		friend class Gizmos;

	public:
		class Buffer : public ShaderBuffer
		{
		public:
			Buffer() : ShaderBuffer(&Data, sizeof(Data))
			{
				Data.Color = D3DXCOLOR(1, 1, 1, 1);
				Data.HighlightColor = D3DXCOLOR(0, 0, 0, 1);
				Data.IsHighlight = 0;
			}
			struct Struct
			{
				D3DXCOLOR Color;
				D3DXCOLOR HighlightColor;
				int IsHighlight;
				int Padding[3];
			}Data;
		};
	public:
		~Gizmo();

		void Render();
		void UpdateVertexData();
	public:
		D3DXCOLOR color, highlightColor;
		D3DXMATRIX rootWorld;
		D3DXMATRIX localWorld;

		vector<VertexColor> vertexData;
		vector<UINT> indexData;
		bool bHighlight;
	private:
		Gizmo();
		Gizmo(vector<D3DXVECTOR3>&& positions, vector<UINT>&& indices);

		void Init();
		void CreateBuffer();

	private:
		D3D11_PRIMITIVE_TOPOLOGY topology;
		WorldBuffer* worldBuffer;
		ID3D11Buffer* vertexBuffer, *indexBuffer;

		Shader* shader;
		Buffer* buffer;
	};

	class Gizmos
	{
	public:
		static Gizmo* Quad(D3DXVECTOR3 center, D3DXVECTOR3 normal, D3DXVECTOR3 up, float width, float height);

		static Gizmo* Cube(D3DXVECTOR3 min, D3DXVECTOR3 max);
		static Gizmo* Sphere(D3DXVECTOR3 center, float radius);
		static Gizmo* Frustum(BoundingFrustum* frustum);

		static Gizmo* Line(D3DXVECTOR3 start, D3DXVECTOR3 end);
		static Gizmo* Ray(D3DXVECTOR3 start, D3DXVECTOR3 dir, float length = 10000.0f);

		static Gizmo* WireCube(D3DXVECTOR3 min, D3DXVECTOR3 max);
		static Gizmo* WireSphere(D3DXVECTOR3 center, float radius);

		static Gizmo* Scale();
		static Gizmo* Rotate();
		static Gizmo* Translate();
	};
}