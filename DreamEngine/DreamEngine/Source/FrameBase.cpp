#include "FrameBase.h"

namespace DreamEngine
{

static CFrameBase* PThis = NULL;

//! message adapter
static LRESULT CALLBACK WndProc(HWND hWnd, uint16 message, WPARAM wParam, LPARAM lParam)
{
	return (PThis->MsgProc(hWnd, message, wParam, lParam));
}

CFrameBase::CFrameBase(CRenderSystem* pRenderSystem):
	CRenderTarget("MianFrameRenderTarget", pRenderSystem),
	m_pTimer(NULL),
	m_pRenderTextureFactory(NULL),
	m_frameWidth(800),
	m_frameHeigth(600)
{
	PThis = this;
}

CFrameBase::~CFrameBase()
{
	PThis = NULL;
}


EngineError CFrameBase::Initialize(const CRenderSystem::CDeviceSetting& opinion)
{
	EngineError error;

	error = CreateMianWindow();
	CheckEngineError(error)
	
	if (m_pRenderSystem==NULL)
	{
		return ERROR_HAVE_NULL_POINT;
	}

	error = m_pRenderSystem->Initialize(m_hWnd, &opinion);
	CheckEngineError(error)
	m_pRenderSystem->GetD3DDevice()->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_pRenderSurface);

	m_pTimer = new CTimer();
	m_pRenderTextureFactory = new CRenderTextureFactory;

	D3DXCreateFont(m_pRenderSystem->GetD3DDevice(),0,0,0,
		0,0,0,0,0,0, "Arial", &m_pFont);

	return ERROR_OK;
}

EngineError CFrameBase::ShutDown()
{
	if (m_pFont != NULL)
	{
		m_pFont->Release();
	}

	SAFE_DELETE(m_pTimer);

	SAFE_DELETE(m_pRenderTextureFactory);

	if (m_pRenderSystem != NULL)
	{
		m_pRenderSystem->Destory();
	}
	
	return ERROR_OK;
}

void CFrameBase::Render()
{
	if (m_pRenderSystem != NULL)
	{
		LPDIRECT3DDEVICE9 pd3dDevice = m_pRenderSystem->GetD3DDevice();

		if (pd3dDevice != NULL)
		{
			if (m_pTimer != NULL)
			{
				m_pTimer->Update();
			}
			if (m_pRenderTextureFactory != NULL)
			{
				m_pRenderTextureFactory->OnRender();
			}

			OnRenderStart();
			//m_pRenderSystem->GetD3DDevice()->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_pRenderSurface);
			m_pRenderSystem->GetD3DDevice()->SetRenderTarget(0, m_pRenderSurface);

			CViewport* pViewport = m_pViewport;
			unsigned int clearBuffer = (pViewport==NULL)?D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER:pViewport->GetClearBuffers();
			CColor backColor		  = (pViewport==NULL)?0xffffffff:pViewport->GetBackColor();

			pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, backColor, 1.0f, 0);

			UpdateMartix();
			if (!FAILED( pd3dDevice->BeginScene()))
			{
				if (m_pRenderSystem->TestDeviceIsLost()==ERROR_DEVICE_TEST_OK)
				{
					CSceneManager* pSceneManager = m_pViewport->GetCamera()->GetSceneManager();
					if (pSceneManager != NULL)
					{
						pSceneManager->OnRender();
					}
					OnRender();
				}

				pd3dDevice->EndScene();
				pd3dDevice->Present( NULL, NULL, NULL, NULL );

				OnRenderEnd();
			}
		}
	}
}


CViewport* CFrameBase::AddViewport(CCamera* pCamera)
{
	pCamera->SetAspectRatio(float(m_frameWidth)/m_frameHeigth);
	CViewport* pViewport = new CViewport(pCamera, m_frameWidth, m_frameHeigth);
	SetViewport(pViewport);

	return pViewport;
}

void CFrameBase::Run()
{
	::ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	::UpdateWindow(m_hWnd);

	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );
	while( msg.message!=WM_QUIT )
	{
		if(::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Render(); 
		}
	}
}

EngineError CFrameBase::CreateMianWindow()
{
	WNDCLASSEX wndClass = { sizeof(WNDCLASSEX), CS_CLASSDC|CS_HREDRAW|CS_VREDRAW, WndProc, 0L, 0L, 
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		TEXT("ClassName"), NULL };
	RegisterClassEx( &wndClass );

	m_hWnd = ::CreateWindow( TEXT("ClassName"), TEXT("Game"), 
		WS_OVERLAPPEDWINDOW-WS_MAXIMIZEBOX-WS_SIZEBOX, CW_USEDEFAULT, 0, m_frameWidth, m_frameHeigth,
		GetDesktopWindow(), NULL, wndClass.hInstance, NULL );


	return ERROR_OK;
}

LRESULT CALLBACK CFrameBase::MsgProc(HWND hWnd, uint16 message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		{
			m_hWnd = hWnd;
			OnWinodwCreate(WindowMesssageStruct(hWnd, wParam, lParam));
		}break;

	case WM_PAINT:
		{
			Render();
			::ValidateRect(hWnd, NULL);
		}break;

	case WM_SIZE:
		{
			OnWindowSized(WindowMesssageStruct(hWnd, wParam, lParam));
		}break;

	case WM_CLOSE:
		{
			OnWindowClose(WindowMesssageStruct(hWnd, wParam, lParam));
		}break;

	case WM_ACTIVATE:
		{

		}break;

	case WM_LBUTTONUP:
		{
			::ReleaseCapture();
		}break;

	case WM_LBUTTONDOWN:
		{
			::SetCapture(hWnd);
		}break;

	case  WM_DESTROY :
		{
			::PostQuitMessage(0);
		}break;
	}

	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

void CFrameBase::SetBackColor(CColor color)
{
	if (m_pRenderSystem!=NULL && m_pViewport!=NULL)
	{
		m_pViewport->SetBackColor(color);
	}
}

CColor CFrameBase::GetBackColor()const
{
	if (m_pRenderSystem!=NULL && m_pViewport!=NULL)
	{
		return m_pViewport->GetBackColor();
	}
	else
	{
		return 0xffffffff;
	}
}

float CFrameBase::GetFPS()const
{
	if (m_pTimer != NULL)
	{
		return m_pTimer->GetFPS();
	}
	return 0.0f;
}

void CFrameBase::DrawTexts(const std::string& text, RECT& area,
	DWORD textFormat/* =DT_SINGLELINE|DT_NOCLIP|DT_CENTER|DT_VCENTER */,
	CColor color/* =0xffffffff */)
{
	if (m_pFont != NULL)
	{
		m_pFont->DrawText(NULL, text.c_str(), text.length(), &area,
			textFormat, color);
	}
}

}
