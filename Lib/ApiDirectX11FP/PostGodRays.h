#pragma once

#include "PostProcessorStep.h"

namespace Vektoria
{
	class CPostGodRays : public CPostProcessorStep
	{
	public:
		CPostGodRays();
		~CPostGodRays();

		void Init(ID3D11DeviceContext* pContext, ID3D11Device* pDevice, CDXUtilities* pDxUtilities, int iWindowWidth, 
				 int iWindowHeight,  unsigned int uiSampleCount, CGeometryUtil* pGeoUtil);
		void InitShader(CShaderCache* pShaderCache);
		void ResizeRT(CViewport* pViewport);
		ID3D11ShaderResourceView* Tick(CViewport* pViewport, D3D11_VIEWPORT* pDXViewport, ID3D11ShaderResourceView* pOpaqueSRV,
									   ID3D11ShaderResourceView* pTransparentSRV, ID3D11ShaderResourceView* pCurrTextureSRV, 
									   CForwardPlusRenderer* pCurrRenderer);
		void Fini();
		bool IsInitialized() const;
	private:

		ID3D11InputLayout* m_pLayout;

		ID3D11VertexShader* m_pGodRayVertex;
		ID3D11PixelShader* m_pGodRayPrePixel[3];
		ID3D11PixelShader* m_pGodRayAccumPixel;
		SPPRENDERTARGET m_renderTargetDepth;
		SPPRENDERTARGET m_renderTargetGodRay;

		ID3D11ShaderResourceView* m_pCurrTextureSRV;

		CGeometryUtil* m_pGeoUtil;
		ID3D11DeviceContext* m_pContext;
		ID3D11Device* m_pDevice;

		CDXUtilities* m_pDxUtilities;

		unsigned int m_uiSampleCount;

		bool m_bInitialized;
	};

}

