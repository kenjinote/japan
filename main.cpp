#define UNICODE
#pragma comment(linker,"/opt:nowin98")
#include<windows.h>
#include"resource.h" 

TCHAR szClassName[]=TEXT("Window");

const RECT hokkaido={333,0,333+300,0+131};
const RECT touhoku={253,128,253+180,128+145};
const RECT hokuriku={202,208,202+128,208+95};
const RECT kanto={280,252,280+68,252+148};
const RECT tokai={202,260,202+88,260+100};
const RECT kansai={171,261,171+62,261+87};
const RECT chugoku={85,235,85+100,235+75};
const RECT shikoku={107,300,107+75,300+50};
const RECT kyushu={24,265,24+88,265+135};
const RECT okinawa={0,0,0+298,0+155};

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	static HBITMAP hBitmap;
	static HBITMAP hOldBitmap;
	static HDC hBuffer;
	switch(msg)
	{
	case WM_CREATE:
		hBitmap=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,MAKEINTRESOURCE(IDB_BITMAP1));
		{
			const HDC hdc=GetDC(0);
			hBuffer=CreateCompatibleDC(hdc);
			ReleaseDC(0,hdc);
			hOldBitmap=(HBITMAP)SelectObject(hBuffer,hBitmap);
		}
		break;
	case WM_MOUSEMOVE:
		{
			const POINT point={LOWORD(lParam),HIWORD(lParam)};
			const HDC hdc=GetDC(hWnd);
			BitBlt(hdc,0,0,600,400,hBuffer,0,0,SRCCOPY);
			if(PtInRect(&hokkaido,point))
			{
				BitBlt(hdc,0,0,600,400,hBuffer,0,400,SRCCOPY);
			}
			else if(PtInRect(&touhoku,point))
			{
				BitBlt(hdc,0,0,600,400,hBuffer,0,800,SRCCOPY);
			}
			else if(PtInRect(&hokuriku,point))
			{
				BitBlt(hdc,0,0,600,400,hBuffer,0,1200,SRCCOPY);
			}
			else if(PtInRect(&kanto,point))
			{
				BitBlt(hdc,0,0,600,400,hBuffer,0,1600,SRCCOPY);
			}
			else if(PtInRect(&tokai,point))
			{
				BitBlt(hdc,0,0,600,400,hBuffer,0,2000,SRCCOPY);
			}
			else if(PtInRect(&kansai,point))
			{
				BitBlt(hdc,0,0,600,400,hBuffer,0,2400,SRCCOPY);
			}
			else if(PtInRect(&chugoku,point))
			{
				BitBlt(hdc,0,0,600,400,hBuffer,0,2800,SRCCOPY);
			}
			else if(PtInRect(&shikoku,point))
			{
				BitBlt(hdc,0,0,600,400,hBuffer,0,3200,SRCCOPY);
			}
			else if(PtInRect(&kyushu,point))
			{
				BitBlt(hdc,0,0,600,400,hBuffer,0,3600,SRCCOPY);
			}
			else if(PtInRect(&okinawa,point))
			{
				BitBlt(hdc,0,0,600,400,hBuffer,0,4000,SRCCOPY);
			}
			ReleaseDC(hWnd,hdc);
		}
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			const HDC hdc=BeginPaint(hWnd,&ps);
			BitBlt(hdc,0,0,600,400,hBuffer,0,0,SRCCOPY);
			EndPaint(hWnd,&ps);
		}
		break;
	case WM_DESTROY:
		SelectObject(hBuffer,hOldBitmap);
		DeleteObject(hBitmap);
		DeleteDC(hBuffer);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd,msg,wParam,lParam);
	}
	return 0;
}

EXTERN_C void __cdecl WinMainCRTStartup()
{
	MSG msg;
	HINSTANCE hInstance=GetModuleHandle(0);
	WNDCLASS wndclass={
		CS_HREDRAW|CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd=CreateWindow(
			szClassName,
			TEXT("Window"),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			0,
			CW_USEDEFAULT,
			0,
			0,
			0,
			hInstance,
			0
		);
	ShowWindow(hWnd,SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	ExitProcess(msg.wParam);
}

#if _DEBUG
void main(){}
#endif
