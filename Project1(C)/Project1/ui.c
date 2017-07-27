#pragma once
#include <Windows.h>
#include"Ball.h"


LONG CALLBACK MainWndProc(
	HWND hwnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
	);

/*----------------------define��--------------------------*/

//������ɫ


#define COLOR_BOUNDARY      RGB(255,255,255)//�߽���ɫ
#define COLOR_BACKG              RGB(255 ,228, 225)//������ɫ
#define COLOR_TEXT                  RGB(0,0,0)
#define Easy    0//���Ѷ�
#define Mid    1//�е��Ѷ�
#define Hard   2//�����Ѷ�

#define CELL_PIXEL			1
/*---------------------------------------------------------*/
// ȫ�ֱ���
HINSTANCE hinst; 
RECT rectBoundary;
Page page = MainPage1;//ҳ��
HBITMAP HBG1;//����1
BOOL LeftPress=FALSE;
BOOL RightPress=FALSE;
int OpenMusic =1 ;//Ĭ�Ͽ�������
int OpenSndEfct = 1;//Ĭ�Ͽ�����Ч
int Diffculty = Easy;//�Ѷ�
int Color = RGB(0xff, 0x30, 0x30);
int ColorHeavy = RGB(0x8B, 0x00, 0x00);
BOOL TimeStop = FALSE;
int ballType =Light;//С������
double BoardColor= (RGB(255, 246, 143));//��ͨľ����ɫ������ʵ����ͨģ���������ֽ����ɫ
double ChangeColor = 0;

/*----------------------------------------------------------*/
//���ֺ���
void OnKeyDown(WPARAM P,HWND hwnd);
void ReSizeGameWnd(HWND hwnd);
void OnKeyUp(WPARAM P, HWND hwnd);
/*----------------------------------------------------------*/
LONG Bg(HWND hwnd);
int WINAPI WinMain(
	HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASS wc;
	HWND hwnd;
	MSG msg;
	int fGotMessage;
	
	//wc.style=CS_HREDRAW|CS_VREDRAW;
	wc.style = CS_HREDRAW | CS_VREDRAW ; //��ֹ�������
	//wc.style = WS_SYSMENU;
	//wc.style = ~WS_MINIMIZEBOX; //��ֹ������С��
	wc.lpfnWndProc=MainWndProc;
	wc.cbClsExtra=0;
	wc.cbWndExtra=0;
	wc.hInstance=hinstance;
	wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);//?
	wc.lpszMenuName="MainMenu";
	wc.lpszClassName="MainWClass";
	RegisterClass(&wc);
	hwnd=CreateWindow(
		"MainWClass",
		"С�ƵĲ�����",
		WS_SYSMENU| WS_MINIMIZEBOX,
		0,
		0,
		336, // ����߽���������߱߿���ȡ�
		691,
		(HWND)NULL,
		(HMENU)NULL,
		hinstance,
		(LPVOID)NULL);
	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);
	while((fGotMessage=GetMessage(&msg,(HWND)NULL,0,0))!=0&&fGotMessage!=-1)
		/*GetMessage��LPMSG lpMsg��HWND hWnd��UINT wMsgFilterMin��UINT wMsgFilterMax)
		���к�������ʾ������Ϣ����Сֵ�����ֵ*/
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;

}
void GamePaint(HWND hwnd)
{
	HPEN hpen;
	HDC hdc, hdcmem;
	HBITMAP hbmMem;
	HBITMAP HBG1;

	HPEN hPenBoundary;
	HPEN hOldPen;

	HBRUSH hOldBrush;
	HBRUSH hBrushBackground;
	HBRUSH hBrushBoard;
	HBRUSH hBrushBall;
	HFONT hFont, hOldFont;
	/*�������ǵ÷Żػ���վ*/
	HBRUSH hBrushBoard2;
	HBRUSH hBrushBoard3;
	HBRUSH hBrushBoard4;
	HBRUSH hBrushBoard5;
	/*-----------------------*/
	//�������ǵ÷Ż���վ
	HBRUSH hBrushSlowBrush;
	HBRUSH hBrushGLBrush;
	HBRUSH hBrushINBrush;
	HBRUSH hBrushTLBrush;
	HBRUSH hBrushTHBrush;
	HPEN NullPen;
	HPEN BlackPen;
	HBRUSH hBrushCTN;
	/*------------------------*/

	/*-----------------------*/
	//HBITMAP hTitle;
	BITMAP bmp;
	PGAME_COORD pBoardBody;
	PGAME_COORD lpBall;
	PGAME_COORD lpProp;
	lpBall = GetBallBody();
	lpProp = GetGameProp();
	RECT rect;
	GetClientRect(hwnd, &rect);
	hdc = GetDC(hwnd);
	hdcmem = CreateCompatibleDC(hdc);
	hbmMem = CreateCompatibleBitmap(hdc,
		rect.right - rect.left, rect.bottom - rect.top);

	SelectObject(hdcmem, hbmMem);

	hpen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	//-------����----------
	hBrushBoard2 = CreateSolidBrush(RGB(0x40, 0x40, 0x40));
	hBrushBoard3=CreateSolidBrush(RGB(147 ,112 ,219));
	hBrushBoard4=CreateSolidBrush(RGB(34, 139, 34));
	hBrushBoard5 = CreateSolidBrush(RGB(0xBF, 0xEF, 0xFF));

	//------------------------------------
	hBrushSlowBrush = CreateSolidBrush(RGB(0x22, 0x8B, 0x22));//��ɫ
	hBrushGLBrush = CreateSolidBrush(RGB(0, 0, 0));//��ɫ
	hBrushINBrush = CreateSolidBrush(RGB(0x47,0x3C,0x8B));//�޵�
	hBrushTLBrush = CreateSolidBrush(Color);          //�죬����1
	hBrushTHBrush = CreateSolidBrush(ColorHeavy);//��죬����1
	NullPen = CreatePen(PS_NULL, 0, RGB(255, 255, 255));
	BlackPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	hBrushCTN = CreateSolidBrush(RGB(255, 136, 24));
    /*----------------������----------------*/





	//��-----����---------------------��-��
	hPenBoundary = CreatePen(0, 5, COLOR_BOUNDARY);
	hBrushBackground = CreateSolidBrush(COLOR_BACKG);
	hBrushBoard= CreateSolidBrush(BoardColor);
	hBrushBall = CreateSolidBrush(Color);
	FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));


	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushBackground);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);

	//������
	HBG1 = LoadImage(NULL, "title.bmp",
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (HBG1 == NULL)
	{
		MessageBox(hwnd, "bmp file not find", "ERROR!",
			MB_OK | MB_ICONERROR);
		//ExitProcess(0);
	}
	SelectObject(hdcmem, HBG1);
	GetObject(HBG1, sizeof(BITMAP), &bmp);
	SetStretchBltMode(hdcmem, STRETCH_HALFTONE);//���ͼƬ����ʧ��

	//StretchBlt(hdcmem,
	//	rectBoundary.left, rectBoundary.top,
	//	rectBoundary.right - rectBoundary.left, rectBoundary.bottom - rectBoundary.top,
	//	hdcmem,
	//	0, 0,
	//	bmp.bmWidth, bmp.bmHeight,
	//	SRCCOPY);

	//������
	Rectangle(hdcmem,
	rectBoundary.left, rectBoundary.top,
	rectBoundary.right, rectBoundary.bottom
	);


	//������
	if (lpProp->type != NoneProp)
	{
		switch (lpProp->type)
		{
		case SpeedUpProp:
			SelectObject(hdcmem, NullPen);
			SelectObject(hdcmem,hBrushBall);
			POINT b[3] = { (lpProp->x + 10)*CELL_PIXEL + rectBoundary.left,lpProp->y*CELL_PIXEL + rectBoundary.top,
				(lpProp->x )*CELL_PIXEL + rectBoundary.left,(lpProp->y + 10)*CELL_PIXEL + rectBoundary.top,
				(lpProp->x +20)*CELL_PIXEL + rectBoundary.left,(lpProp->y + 10)*CELL_PIXEL + rectBoundary.top
			};
			Polygon(hdcmem, b, 3);
			Rectangle(hdcmem,
				(lpProp->x+6) * CELL_PIXEL + rectBoundary.left,
				(lpProp->y+10) * CELL_PIXEL + rectBoundary.top,
				(lpProp->x + 15)*CELL_PIXEL + rectBoundary.left,
				(lpProp->y + 19)*CELL_PIXEL + rectBoundary.top);
			break;
		case SlowTimeProp:
			SelectObject(hdcmem, NullPen);
			SelectObject(hdcmem, hBrushSlowBrush);
			Rectangle(hdcmem,
				(lpProp->x + 6) * CELL_PIXEL + rectBoundary.left,
				(lpProp->y ) * CELL_PIXEL + rectBoundary.top,
				(lpProp->x + 15)*CELL_PIXEL + rectBoundary.left,
				(lpProp->y + 10)*CELL_PIXEL + rectBoundary.top);
			POINT c[3] = { (lpProp->x + 10)*CELL_PIXEL + rectBoundary.left,(lpProp->y+17)*CELL_PIXEL + rectBoundary.top,
				(lpProp->x)*CELL_PIXEL + rectBoundary.left,(lpProp->y + 9)*CELL_PIXEL + rectBoundary.top,
				(lpProp->x + 20)*CELL_PIXEL + rectBoundary.left,(lpProp->y + 9)*CELL_PIXEL + rectBoundary.top
			};
			Polygon(hdcmem, c, 3);
			break;
		case InvincibleProp:
			SelectObject(hdcmem, hBrushINBrush);
			SelectObject(hdcmem, NullPen);
			POINT d[3] = { (lpProp->x + 10)*CELL_PIXEL + rectBoundary.left,(lpProp->y )*CELL_PIXEL + rectBoundary.top,
				(lpProp->x+2)*CELL_PIXEL + rectBoundary.left,(lpProp->y + 14)*CELL_PIXEL + rectBoundary.top,
				(lpProp->x + 18)*CELL_PIXEL + rectBoundary.left,(lpProp->y + 14)*CELL_PIXEL + rectBoundary.top
			};
			POINT e[3] = { (lpProp->x + 10)*CELL_PIXEL + rectBoundary.left,(lpProp->y + 18)*CELL_PIXEL + rectBoundary.top,
				(lpProp->x+2)*CELL_PIXEL + rectBoundary.left,(lpProp->y + 4)*CELL_PIXEL + rectBoundary.top,
				(lpProp->x + 18)*CELL_PIXEL + rectBoundary.left,(lpProp->y + 4)*CELL_PIXEL + rectBoundary.top
			};
			Polygon(hdcmem, d, 3);
			Polygon(hdcmem, e, 3);
			break;
		case GetLifeProp:
			SelectObject(hdcmem, BlackPen);
			MoveToEx(hdcmem, lpProp->x+5+rectBoundary.left, lpProp->y+4+rectBoundary.top, NULL);
			LineTo(hdcmem, lpProp->x+5+rectBoundary.left, lpProp->y +14+ rectBoundary.top);
			MoveToEx(hdcmem, lpProp->x  + rectBoundary.left, lpProp->y +9+ rectBoundary.top, NULL);
			LineTo(hdcmem, lpProp->x + 10 + rectBoundary.left, lpProp->y + 9 + rectBoundary.top);
			MoveToEx(hdcmem, lpProp->x+17 + rectBoundary.left, lpProp->y  + rectBoundary.top, NULL);
			LineTo(hdcmem, lpProp->x + 17 + rectBoundary.left, lpProp->y + 16 + rectBoundary.top);
			break;
		case ChangeAllProp:
			SelectObject(hdcmem, hBrushCTN);
			SelectObject(hdcmem, NullPen);
			Rectangle(hdcmem,
				lpProp->x * CELL_PIXEL + rectBoundary.left,
				lpProp->y * CELL_PIXEL + rectBoundary.top,
				(lpProp->x + 19)*CELL_PIXEL + rectBoundary.left,
				(lpProp->y + 19)*CELL_PIXEL + rectBoundary.top);
			break;
		case ChangeTailProp:
			SelectObject(hdcmem, hBrushBoard2);
			SelectObject(hdcmem, NullPen);
			Rectangle(hdcmem,
				lpProp->x * CELL_PIXEL + rectBoundary.left,
				lpProp->y * CELL_PIXEL + rectBoundary.top,
				(lpProp->x + 19)*CELL_PIXEL + rectBoundary.left,
				(lpProp->y + 19)*CELL_PIXEL + rectBoundary.top);
			break;
		case CTTLight:
			SelectObject(hdcmem, NullPen);
			SelectObject(hdcmem, hBrushBall);
			Rectangle(hdcmem,
				(lpProp->x ) * CELL_PIXEL + rectBoundary.left,
				(lpProp->y+2) * CELL_PIXEL + rectBoundary.top,
				(lpProp->x + 10)*CELL_PIXEL + rectBoundary.left,
				(lpProp->y + 7)*CELL_PIXEL + rectBoundary.top);
			POINT f[3] = { (lpProp->x + 9)*CELL_PIXEL + rectBoundary.left,(lpProp->y-1 )*CELL_PIXEL + rectBoundary.top,
				(lpProp->x+9)*CELL_PIXEL + rectBoundary.left,(lpProp->y + 8)*CELL_PIXEL + rectBoundary.top,
				(lpProp->x + 20)*CELL_PIXEL + rectBoundary.left,(lpProp->y + 4)*CELL_PIXEL + rectBoundary.top
			};
			Polygon(hdcmem, f, 3);
			Rectangle(hdcmem,
				(lpProp->x+9) * CELL_PIXEL + rectBoundary.left,
				(lpProp->y + 11) * CELL_PIXEL + rectBoundary.top,
				(lpProp->x + 20)*CELL_PIXEL + rectBoundary.left,
				(lpProp->y + 16)*CELL_PIXEL + rectBoundary.top);
			POINT g[3] = { (lpProp->x )*CELL_PIXEL + rectBoundary.left,(lpProp->y+12)*CELL_PIXEL + rectBoundary.top,
				(lpProp->x + 10)*CELL_PIXEL + rectBoundary.left,(lpProp->y + 7)*CELL_PIXEL + rectBoundary.top,
				(lpProp->x + 10)*CELL_PIXEL + rectBoundary.left,(lpProp->y + 18)*CELL_PIXEL + rectBoundary.top
			};
			Polygon(hdcmem, g, 3);
			break;
		case CTTHeavy:
			SelectObject(hdcmem, NullPen);
			SelectObject(hdcmem, hBrushTHBrush);
			Rectangle(hdcmem,
				(lpProp->x) * CELL_PIXEL + rectBoundary.left,
				(lpProp->y + 2) * CELL_PIXEL + rectBoundary.top,
				(lpProp->x + 10)*CELL_PIXEL + rectBoundary.left,
				(lpProp->y + 7)*CELL_PIXEL + rectBoundary.top);
			POINT h[3] = { (lpProp->x + 9)*CELL_PIXEL + rectBoundary.left,(lpProp->y - 1)*CELL_PIXEL + rectBoundary.top,
				(lpProp->x + 9)*CELL_PIXEL + rectBoundary.left,(lpProp->y + 8)*CELL_PIXEL + rectBoundary.top,
				(lpProp->x + 20)*CELL_PIXEL + rectBoundary.left,(lpProp->y + 4)*CELL_PIXEL + rectBoundary.top
			};
			Polygon(hdcmem, h, 3);
			Rectangle(hdcmem,
				(lpProp->x + 9) * CELL_PIXEL + rectBoundary.left,
				(lpProp->y + 11) * CELL_PIXEL + rectBoundary.top,
				(lpProp->x + 20)*CELL_PIXEL + rectBoundary.left,
				(lpProp->y + 16)*CELL_PIXEL + rectBoundary.top);
			POINT i[3] = { (lpProp->x)*CELL_PIXEL + rectBoundary.left,(lpProp->y + 12)*CELL_PIXEL + rectBoundary.top,
				(lpProp->x + 10)*CELL_PIXEL + rectBoundary.left,(lpProp->y + 7)*CELL_PIXEL + rectBoundary.top,
				(lpProp->x + 10)*CELL_PIXEL + rectBoundary.left,(lpProp->y + 18)*CELL_PIXEL + rectBoundary.top
			};
			Polygon(hdcmem, i, 3);
			break;
		default:
			SelectObject(hdcmem, hpen);
			SelectObject(hdcmem, hBrushBall);
			Rectangle(hdcmem,
			lpProp->x * CELL_PIXEL + rectBoundary.left,
			lpProp->y * CELL_PIXEL + rectBoundary.top,
			(lpProp->x + 19)*CELL_PIXEL + rectBoundary.left,
			(lpProp->y + 19)*CELL_PIXEL + rectBoundary.top);
			break;

		}

		/*SelectObject(hdcmem, hpen);
		SelectObject(hdcmem, hBrushBall);
		Rectangle(hdcmem,
		lpProp->x * CELL_PIXEL + rectBoundary.left,
		lpProp->y * CELL_PIXEL + rectBoundary.top,
		(lpProp->x + 19)*CELL_PIXEL + rectBoundary.left,
		(lpProp->y + 19)*CELL_PIXEL + rectBoundary.top);*/
	}
	
	//��ľ��
	SelectObject(hdcmem, hpen);
	for (int i = 0; i < GetBoardNum(); i++)
	{
		pBoardBody = (PGAME_COORD)board_get_at(i);
        if(pBoardBody->type!=bNone)
		{
			if (pBoardBody->type == bWithTrap)
			{
				SelectObject(hdcmem, hBrushBoard2);
				for (int j = 0; j < 5; j++)
				{
					if (pBoardBody->y > 580)
					{
						POINT a[3] = { (pBoardBody->x + j * 20+10)*CELL_PIXEL + rectBoundary.left,pBoardBody->y*CELL_PIXEL + rectBoundary.top,
							(pBoardBody->x + j * 20)*CELL_PIXEL + rectBoundary.left,600+ rectBoundary.top,
							(pBoardBody->x + j * 20 + 20)*CELL_PIXEL + rectBoundary.left,600+ rectBoundary.top
						};
						Polygon(hdcmem, a, 3);
					}
					else {
						POINT a[3] = { (pBoardBody->x + j * 20+10)*CELL_PIXEL + rectBoundary.left,pBoardBody->y*CELL_PIXEL + rectBoundary.top,
						(pBoardBody->x + j * 20)*CELL_PIXEL + rectBoundary.left,(pBoardBody->y + 20)*CELL_PIXEL + rectBoundary.top,
						(pBoardBody->x + j * 20 + 20)*CELL_PIXEL + rectBoundary.left,(pBoardBody->y + 20)*CELL_PIXEL + rectBoundary.top
						};
						Polygon(hdcmem, a, 3);
					}
				}
			}
			else
			{
				switch (pBoardBody->type) {
				case bNormal:
					SelectObject(hdcmem, hBrushBoard);
					break;
				case bLMoving:
					SelectObject(hdcmem, hBrushBoard3);
					break;
				case bRmoving:
					SelectObject(hdcmem, hBrushBoard3);
					break;
				case bJumping:
					SelectObject(hdcmem, hBrushBoard4);
					break;
				case bBroken:
					SelectObject(hdcmem, hBrushBoard5);
					break;
				default:
					break;
				}
				if (pBoardBody->y > 580)
				{
					Rectangle(hdcmem,
						pBoardBody->x*CELL_PIXEL + rectBoundary.left,
						pBoardBody->y*CELL_PIXEL + rectBoundary.top,
						(pBoardBody->x + 100)*CELL_PIXEL + rectBoundary.left,
						600 + rectBoundary.top
					);
				}
				else
				{
					Rectangle(hdcmem,
						pBoardBody->x*CELL_PIXEL + rectBoundary.left,
						pBoardBody->y*CELL_PIXEL + rectBoundary.top,
						(pBoardBody->x + 100)*CELL_PIXEL + rectBoundary.left,
						(pBoardBody->y + 20)*CELL_PIXEL + rectBoundary.top
					);
				}
			}
		}
	}
	//��С��
	switch (GetBallOneType())
	{
	case Light:
		if(isInvincible())SelectObject(hdcmem, hBrushCTN);
		else SelectObject(hdcmem, hBrushBall);
		break;
	case Heavy:
		if (isInvincible())SelectObject(hdcmem, hBrushCTN);
		 else SelectObject(hdcmem, hBrushTHBrush);
	default:
		break;
	}
	SelectObject(hdcmem, hpen);
	if (isInvincible())
	{
		Ellipse(hdcmem,
			(lpBall->x-10) * CELL_PIXEL + rectBoundary.left,
			(lpBall->y-10) * CELL_PIXEL + rectBoundary.top,
			(lpBall->x + 20)*CELL_PIXEL + rectBoundary.left,
			(lpBall->y + 20)*CELL_PIXEL + rectBoundary.top);

	}
	else
	{
		Ellipse(hdcmem,
			lpBall->x * CELL_PIXEL + rectBoundary.left,
			lpBall->y * CELL_PIXEL + rectBoundary.top,
			(lpBall->x + 20)*CELL_PIXEL + rectBoundary.left,
			(lpBall->y + 20)*CELL_PIXEL + rectBoundary.top);
	}
	//����������
	SelectObject(hdcmem, hBrushBoard2);

	for (int j = 0; j < 15; j++)
	{
		POINT a[3] = {  j*20 + rectBoundary.left,0*CELL_PIXEL + rectBoundary.top,
			(j*20+20)*CELL_PIXEL + rectBoundary.left,0*CELL_PIXEL + rectBoundary.top,
			(j*20 + 10)*CELL_PIXEL + rectBoundary.left,CELL_PIXEL + rectBoundary.top+20
		};
		Polygon(hdcmem, a, 3);
	}


	// ������һ���������
	hFont = CreateFont(-20, -10, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("΢���ź�"));

	// �����FONT�������DC��
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
	{
		CHAR szSourceInfo[1024];
		wsprintf(szSourceInfo, "���� %d   ���� %d", GetScore(), GetLife());
		// ���������ɫ
		SetTextColor(hdcmem, RGB(30 ,144 ,255));
		//�������屳��͸��
		SetBkMode(hdcmem, TRANSPARENT);
		// ����ַ�����
		TextOut(hdcmem, rectBoundary.left + 3, rectBoundary.bottom + 3,
			szSourceInfo, lstrlen(szSourceInfo));
		// �����ɣ���ԭ�����������Ż�DC��
		SelectObject(hdcmem, hOldFont);
	}
	

	BitBlt(hdc,
		0, 0, rect.right - rect.left, rect.bottom - rect.top,
		hdcmem, 0, 0, SRCCOPY);
	//��������
	DeleteObject(hbmMem);
	DeleteObject(HBG1);
	DeleteObject(hdcmem);
	DeleteObject(hpen);
	DeleteObject(hPenBoundary);
	DeleteObject(hFont);
	DeleteObject(hBrushBoard);
	DeleteObject(hBrushBoard2);
	DeleteObject(hBrushBoard3);
	DeleteObject(hBrushBoard4);
	DeleteObject(hBrushBoard5);
	DeleteObject(hBrushBall);
	DeleteObject(hOldBrush);
	DeleteObject(hOldPen);
	DeleteObject(hOldFont);
	//-------------
	DeleteObject(hBrushSlowBrush);
	DeleteObject(hBrushGLBrush);
	DeleteObject(hBrushINBrush);
	DeleteObject(hBrushTLBrush);
	DeleteObject(hBrushTHBrush);
	DeleteObject(NullPen);
	DeleteObject(BlackPen);
	DeleteObject(hBrushCTN);
	//---------------
	DeleteObject(hBrushBackground);
	DeleteDC(hdcmem);
	ReleaseDC(hwnd, hdc);


}
void MainPaint(HWND hwnd)
{
	//CreateThread(NULL, 0, StopMusic, NULL, 0, NULL);
	HPEN hpen;
	HDC hdc, hdcmem;
	HBITMAP hbmMem;
	HBITMAP HBG1;

	HPEN hPenBoundary;
	HPEN hOldPen;

	HBRUSH hOldBrush;
	HBRUSH hBrushBackground;
	HFONT hFont, hOldFont;

	//HBITMAP hTitle;
	BITMAP bmp;

	RECT rect;

	GetClientRect(hwnd, &rect);

	hdc = GetDC(hwnd);

	hdcmem = CreateCompatibleDC(hdc);
	hbmMem = CreateCompatibleBitmap(hdc,
		rect.right - rect.left, rect.bottom - rect.top);

	SelectObject(hdcmem, hbmMem);

	hpen = CreatePen(PS_SOLID, 1, RGB(5, 5, 5));
	hPenBoundary = CreatePen(0, 5, COLOR_BOUNDARY);
	hBrushBackground = CreateSolidBrush(COLOR_BACKG);

	FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushBackground);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);

	
	//������
	HBG1= LoadImage(NULL, "title.bmp",
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	if (HBG1 == NULL)
	{
		MessageBox(hwnd, "bmp file not find", "ERROR!",
			MB_OK | MB_ICONERROR);
		//ExitProcess(0);
	}
	SelectObject(hdcmem, HBG1);
	GetObject(HBG1, sizeof(BITMAP), &bmp);
	SetStretchBltMode(hdcmem, STRETCH_HALFTONE);//���ͼƬ����ʧ��

	StretchBlt(hdcmem,
		rectBoundary.left, rectBoundary.top,
		rectBoundary.right - rectBoundary.left, rectBoundary.bottom - rectBoundary.top,
		hdcmem,
		0, 0,
		bmp.bmWidth, bmp.bmHeight,
		SRCCOPY);
	
	//������

	/*Rectangle(hdcmem,
		rectBoundary.left, rectBoundary.top,
		rectBoundary.right, rectBoundary.bottom
	);*/
	//���߽�

	SelectObject(hdcmem, hPenBoundary);
	MoveToEx(hdcmem, rectBoundary.left, rectBoundary.top, NULL);
	// ����һ��������ʾLineTo����
	LineTo(hdcmem, rectBoundary.left, rectBoundary.bottom);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.bottom);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.top);
	LineTo(hdcmem, rectBoundary.left, rectBoundary.top);
	//д��

	hFont = CreateFont(-30, 0, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("΢���ź�"));

	// �����FONT�������DC��
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
	{
		CHAR szSourceInfo[1024];
		wsprintf(szSourceInfo, "��ʼ��Ϸ");
		// ���������ɫ
		SetTextColor(hdcmem, COLOR_TEXT);
		//�������屳��͸��
		SetBkMode(hdcmem, TRANSPARENT);
		// ����ַ�����
		TextOut(hdcmem, (rectBoundary.left + rectBoundary.right)/2-60, (rectBoundary.bottom+rectBoundary.top)/2 - 100,
			szSourceInfo, lstrlen(szSourceInfo));
		// �����ɣ���ԭ�����������Ż�DC��
		SelectObject(hdcmem, hOldFont);
	}
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
	{
		CHAR szSourceInfo[1024];
		wsprintf(szSourceInfo, "��Ϸ����");
		// ���������ɫ
		SetTextColor(hdcmem, COLOR_TEXT);
		//�������屳��͸��
		SetBkMode(hdcmem, TRANSPARENT);
		// ����ַ�����
		TextOut(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 60, (rectBoundary.bottom + rectBoundary.top) / 2 - 40,
			szSourceInfo, lstrlen(szSourceInfo));
		// �����ɣ���ԭ�����������Ż�DC��
		SelectObject(hdcmem, hOldFont);
	}
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
	{
		CHAR szSourceInfo[1024];
		wsprintf(szSourceInfo, "�˳���Ϸ");
		// ���������ɫ
		SetTextColor(hdcmem, COLOR_TEXT);
		//�������屳��͸��
		SetBkMode(hdcmem,TRANSPARENT);
		// ����ַ�����
		TextOut(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 60, (rectBoundary.bottom + rectBoundary.top) / 2+20 ,
			szSourceInfo, lstrlen(szSourceInfo));
		// �����ɣ���ԭ�����������Ż�DC��
		SelectObject(hdcmem, hOldFont);
	}

	//��ѡ���
	switch (page) {
	case MainPage1:
		MoveToEx(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 65, (rectBoundary.bottom + rectBoundary.top) / 2 - 100, NULL);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 65, (rectBoundary.bottom + rectBoundary.top) / 2 - 100+40);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 + 65, (rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 40);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 + 65, (rectBoundary.bottom + rectBoundary.top) / 2 - 100);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 65, (rectBoundary.bottom + rectBoundary.top) / 2 - 100 );
		break;
	case MainPage2:
		MoveToEx(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 65, (rectBoundary.bottom + rectBoundary.top) / 2 - 40, NULL);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 65, (rectBoundary.bottom + rectBoundary.top) / 2 - 40 + 40);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 + 65, (rectBoundary.bottom + rectBoundary.top) / 2 - 40 + 40);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 + 65, (rectBoundary.bottom + rectBoundary.top) / 2 - 40);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 65, (rectBoundary.bottom + rectBoundary.top) / 2 - 40);
		break;
	case MainPage3:
		MoveToEx(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 65, (rectBoundary.bottom + rectBoundary.top) / 2 +20, NULL);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 65, (rectBoundary.bottom + rectBoundary.top) / 2 +20 + 40);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 + 65, (rectBoundary.bottom + rectBoundary.top) / 2 +20 + 40);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 + 65, (rectBoundary.bottom + rectBoundary.top) / 2 +20);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 65, (rectBoundary.bottom + rectBoundary.top) / 2 +20);
		break;
	default:
		break;
	}

	BitBlt(hdc,
		0, 0, rect.right - rect.left, rect.bottom - rect.top,
		hdcmem, 0, 0, SRCCOPY);

	DeleteObject(hbmMem);
	DeleteObject(HBG1);
	DeleteObject(hdcmem);
	DeleteObject(hpen);
	DeleteObject(hPenBoundary);
	DeleteObject(hFont);
	DeleteObject(hOldBrush);
	DeleteObject(hOldPen);
	DeleteObject(hOldFont);

	DeleteObject(hBrushBackground);
	DeleteDC(hdcmem);
	ReleaseDC(hwnd, hdc);
}
void OptionPaint(HWND hwnd)
{
	//CreateThread(NULL, 0, StopMusic, NULL, 0, NULL);
	HPEN hpen;
	HDC hdc, hdcmem;
	HBITMAP hbmMem;
	HBITMAP HBG1;

	HPEN hPenBoundary;
	HPEN hOldPen;

	HBRUSH hOldBrush;
	HBRUSH hBrushBackground;
	HFONT hFont, hOldFont;
	/*�������ʻ�ˢ���ǵ�ɾ��*/
	HBRUSH hBrushOptionOne;
	HBRUSH hBrushOptionTwo;
	/*-------------------------*/
	//HBITMAP hTitle;
	BITMAP bmp;

	RECT rect;

	GetClientRect(hwnd, &rect);

	hdc = GetDC(hwnd);

	hdcmem = CreateCompatibleDC(hdc);
	hbmMem = CreateCompatibleBitmap(hdc,
		rect.right - rect.left, rect.bottom - rect.top);

	SelectObject(hdcmem, hbmMem);

	hpen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	hPenBoundary = CreatePen(0, 5, COLOR_BOUNDARY);
	hBrushBackground = CreateSolidBrush(COLOR_BACKG);

	hBrushOptionOne = CreateSolidBrush(RGB(0XB5,0XB5,0XB5));//ǳ��
	hBrushOptionTwo = CreateSolidBrush(RGB(0X59, 0X59, 0X59));//���

	FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushBackground);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);


	//������
	HBG1 = LoadImage(NULL, "title.bmp",
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (HBG1 == NULL)
	{
		MessageBox(hwnd, "bmp file not find", "ERROR!",
			MB_OK | MB_ICONERROR);
		//ExitProcess(0);
	}
	SelectObject(hdcmem, HBG1);
	GetObject(HBG1, sizeof(BITMAP), &bmp);
	SetStretchBltMode(hdcmem, STRETCH_HALFTONE);//���ͼƬ����ʧ��

	StretchBlt(hdcmem,
		rectBoundary.left, rectBoundary.top,
		rectBoundary.right - rectBoundary.left, rectBoundary.bottom - rectBoundary.top,
		hdcmem,
		0, 0,
		bmp.bmWidth, bmp.bmHeight,
		SRCCOPY);

	//������

	/*Rectangle(hdcmem,
	rectBoundary.left, rectBoundary.top,
	rectBoundary.right, rectBoundary.bottom
	);*/
	//���߽�

	SelectObject(hdcmem, hPenBoundary);
	MoveToEx(hdcmem, rectBoundary.left, rectBoundary.top, NULL);
	// ����һ��������ʾLineTo����
	LineTo(hdcmem, rectBoundary.left, rectBoundary.bottom);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.bottom);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.top);
	LineTo(hdcmem, rectBoundary.left, rectBoundary.top);
	//д��

	hFont = CreateFont(-25, 0, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("΢���ź�"));

	// �����FONT�������DC��
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
	{
		CHAR szSourceInfo[1024];
		wsprintf(szSourceInfo, "��Ϸ�Ѷ�");
		// ���������ɫ
		SetTextColor(hdcmem, COLOR_TEXT);
		//�������屳��͸��
		SetBkMode(hdcmem, TRANSPARENT);
		// ����ַ�����
		TextOut(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 100, (rectBoundary.bottom + rectBoundary.top) / 2 - 100,
			szSourceInfo, lstrlen(szSourceInfo));
		// �����ɣ���ԭ�����������Ż�DC��
		SelectObject(hdcmem, hOldFont);
	}
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
	{
		CHAR szSourceInfo[1024];
		wsprintf(szSourceInfo, "С������");
		// ���������ɫ
		SetTextColor(hdcmem, COLOR_TEXT);
		//�������屳��͸��
		SetBkMode(hdcmem, TRANSPARENT);
		// ����ַ�����
		TextOut(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 100, (rectBoundary.bottom + rectBoundary.top) / 2 - 60,
			szSourceInfo, lstrlen(szSourceInfo));
		// �����ɣ���ԭ�����������Ż�DC��
		SelectObject(hdcmem, hOldFont);
	}
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
	{
		CHAR szSourceInfo[1024];
		wsprintf(szSourceInfo, "����");
		// ���������ɫ
		SetTextColor(hdcmem, COLOR_TEXT);
		//�������屳��͸��
		SetBkMode(hdcmem, TRANSPARENT);
		// ����ַ�����
		TextOut(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 100, (rectBoundary.bottom + rectBoundary.top) / 2 -20,
			szSourceInfo, lstrlen(szSourceInfo));
		// �����ɣ���ԭ�����������Ż�DC��
		SelectObject(hdcmem, hOldFont);
	}
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
	{
		CHAR szSourceInfo[1024];
		wsprintf(szSourceInfo, "��Ч");
		// ���������ɫ
		SetTextColor(hdcmem, COLOR_TEXT);
		//�������屳��͸��
		SetBkMode(hdcmem, TRANSPARENT);
		// ����ַ�����
		TextOut(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 100, (rectBoundary.bottom + rectBoundary.top) / 2 + 20,
			szSourceInfo, lstrlen(szSourceInfo));
		// �����ɣ���ԭ�����������Ż�DC��
		SelectObject(hdcmem, hOldFont);
	}
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
	{
		CHAR szSourceInfo[1024];
		wsprintf(szSourceInfo, "���沢����");
		// ���������ɫ
		SetTextColor(hdcmem, COLOR_TEXT);
		//�������屳��͸��
		SetBkMode(hdcmem, TRANSPARENT);
		// ����ַ�����
		TextOut(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 -50, (rectBoundary.bottom + rectBoundary.top) / 2 + 100,
			szSourceInfo, lstrlen(szSourceInfo));
		// �����ɣ���ԭ�����������Ż�DC��
		SelectObject(hdcmem, hOldFont);
	}

	//��ѡ���
	switch (page) {
	case OptionPage1:
		MoveToEx(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 105, (rectBoundary.bottom + rectBoundary.top) / 2 - 100 - 1, NULL);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 105, (rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 35);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 + 125, (rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 35);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 + 125, (rectBoundary.bottom + rectBoundary.top) / 2 - 100 - 1);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 105, (rectBoundary.bottom + rectBoundary.top) / 2 - 100 - 1);
		break;
	case OptionPage2:
		MoveToEx(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 105, (rectBoundary.bottom + rectBoundary.top) / 2 - 60 - 1, NULL);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 105, (rectBoundary.bottom + rectBoundary.top) / 2 - 60 + 35);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 + 125, (rectBoundary.bottom + rectBoundary.top) / 2 - 60 + 35);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 + 125, (rectBoundary.bottom + rectBoundary.top) / 2 - 60 - 1);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 105, (rectBoundary.bottom + rectBoundary.top) / 2 - 60 - 1);
		break;
	case OptionPage3:
		MoveToEx(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 105, (rectBoundary.bottom + rectBoundary.top) / 2 - 20 - 1, NULL);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 105, (rectBoundary.bottom + rectBoundary.top) / 2 - 20 + 35);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 + 125, (rectBoundary.bottom + rectBoundary.top) / 2 - 20 + 35);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 + 125, (rectBoundary.bottom + rectBoundary.top) / 2 - 20 - 1);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 105, (rectBoundary.bottom + rectBoundary.top) / 2 - 20 - 1);
		break;
	case OptionPage4:
		MoveToEx(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 105, (rectBoundary.bottom + rectBoundary.top) / 2 + 20 - 1, NULL);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 105, (rectBoundary.bottom + rectBoundary.top) / 2 + 20 + 35);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 + 125, (rectBoundary.bottom + rectBoundary.top) / 2 + 20 + 35);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 + 125, (rectBoundary.bottom + rectBoundary.top) / 2 + 20 - 1);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 105, (rectBoundary.bottom + rectBoundary.top) / 2 + 20 - 1);
		break;
	case OptionPage5:
		MoveToEx(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 55, (rectBoundary.bottom + rectBoundary.top) / 2 + 100 - 1, NULL);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 55, (rectBoundary.bottom + rectBoundary.top) / 2 + 100 + 35);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 + 79, (rectBoundary.bottom + rectBoundary.top) / 2 + 100 + 35);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 + 79, (rectBoundary.bottom + rectBoundary.top) / 2 + 100 - 1);
		LineTo(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 - 55, (rectBoundary.bottom + rectBoundary.top) / 2 + 100 - 1);
		break;
	default:
		break;
	}
	//�õĽ�������ʼ������ѡ��
		SelectObject(hdcmem, hpen);
		if (Diffculty == Easy)SelectObject(hdcmem, hBrushOptionOne);
		else SelectObject(hdcmem, hBrushOptionTwo);
		POINT j[3] = { ((rectBoundary.left + rectBoundary.right) / 2 + 65 - 35) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 8) + rectBoundary.top,
			((rectBoundary.left + rectBoundary.right) / 2 + 65 - 15) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 - 13 + 8) + rectBoundary.top,
			((rectBoundary.left + rectBoundary.right) / 2 + 65 - 15) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 12 + 8) + rectBoundary.top
		};
		Polygon(hdcmem, j, 3);
		if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
		{
			CHAR szSourceInfo[1024];
			switch (Diffculty)
			{
			case Easy:
				wsprintf(szSourceInfo, "��");
				break;
			case Mid:
				wsprintf(szSourceInfo, "��");
				break;
			case Hard:
				wsprintf(szSourceInfo, "��");
				break;
			default:
				break;
			}
			// ���������ɫ
			SetTextColor(hdcmem, COLOR_TEXT);
			//�������屳��͸��
			SetBkMode(hdcmem, TRANSPARENT);
			// ����ַ�����
			TextOut(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 +65, (rectBoundary.bottom + rectBoundary.top) / 2 - 100,
				szSourceInfo, lstrlen(szSourceInfo));
			// �����ɣ���ԭ�����������Ż�DC��
			SelectObject(hdcmem, hOldFont);
		}
		if (Diffculty == Hard)SelectObject(hdcmem, hBrushOptionOne);
		else SelectObject(hdcmem, hBrushOptionTwo);
		POINT k[3] = { ((rectBoundary.left + rectBoundary.right) / 2 + 65 +40) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 8) + rectBoundary.top,
			((rectBoundary.left + rectBoundary.right) / 2 + 65 + 20) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 - 13 + 8) + rectBoundary.top,
			((rectBoundary.left + rectBoundary.right) / 2 + 65 +20) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 12 + 8) + rectBoundary.top
		};
		Polygon(hdcmem, k, 3);
		if (ballType==Light)SelectObject(hdcmem, hBrushOptionOne);
		else SelectObject(hdcmem, hBrushOptionTwo);
		POINT l[3] = { ((rectBoundary.left + rectBoundary.right) / 2 + 65 - 35) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 48) + rectBoundary.top,
			((rectBoundary.left + rectBoundary.right) / 2 + 65 - 15) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 - 13 + 48) + rectBoundary.top,
			((rectBoundary.left + rectBoundary.right) / 2 + 65 - 15) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 12 + 48) + rectBoundary.top
		};
		Polygon(hdcmem, l, 3);
		if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
		{
			CHAR szSourceInfo[1024];
			switch (ballType)
			{
			case Light:
				wsprintf(szSourceInfo, "��");
				break;
			case Heavy:
				wsprintf(szSourceInfo, "��");
				break;
			default:
				break;
			}
			// ���������ɫ
			SetTextColor(hdcmem, COLOR_TEXT);
			//�������屳��͸��
			SetBkMode(hdcmem, TRANSPARENT);
			// ����ַ�����
			TextOut(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 + 65, (rectBoundary.bottom + rectBoundary.top) / 2 - 100+40,
				szSourceInfo, lstrlen(szSourceInfo));
			// �����ɣ���ԭ�����������Ż�DC��
			SelectObject(hdcmem, hOldFont);
		}
		if (ballType == Heavy)SelectObject(hdcmem, hBrushOptionOne);
		else SelectObject(hdcmem, hBrushOptionTwo);
		POINT m[3] = { ((rectBoundary.left + rectBoundary.right) / 2 + 65 + 40) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 48) + rectBoundary.top,
			((rectBoundary.left + rectBoundary.right) / 2 + 65 + 20) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 - 13 + 48) + rectBoundary.top,
			((rectBoundary.left + rectBoundary.right) / 2 + 65 + 20) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 12 +48) + rectBoundary.top
		};
		Polygon(hdcmem, m, 3);
		if (OpenMusic == 1)SelectObject(hdcmem, hBrushOptionOne);
		else SelectObject(hdcmem, hBrushOptionTwo);

		POINT n[3] = { ((rectBoundary.left + rectBoundary.right) / 2 + 65 - 35) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 88) + rectBoundary.top,
			((rectBoundary.left + rectBoundary.right) / 2 + 65 - 15) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 - 13 + 88) + rectBoundary.top,
			((rectBoundary.left + rectBoundary.right) / 2 + 65 - 15) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 12 + 88) + rectBoundary.top
		};
		Polygon(hdcmem, n, 3);
		if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
		{
			CHAR szSourceInfo[1024];
			switch (OpenMusic)
			{
			case 1:
				wsprintf(szSourceInfo, "��");
				break;
			case 0:
				wsprintf(szSourceInfo, "��");
				break;
			default:
				break;
			}
			// ���������ɫ
			SetTextColor(hdcmem, COLOR_TEXT);
			//�������屳��͸��
			SetBkMode(hdcmem, TRANSPARENT);
			// ����ַ�����
			TextOut(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 + 65, (rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 80,
				szSourceInfo, lstrlen(szSourceInfo));
			// �����ɣ���ԭ�����������Ż�DC��
			SelectObject(hdcmem, hOldFont);
		}
		if (OpenMusic==0)SelectObject(hdcmem, hBrushOptionOne);
		else SelectObject(hdcmem, hBrushOptionTwo);
		POINT o[3] = { ((rectBoundary.left + rectBoundary.right) / 2 + 65 + 40) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 88) + rectBoundary.top,
			((rectBoundary.left + rectBoundary.right) / 2 + 65 + 20) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 - 13 + 88) + rectBoundary.top,
			((rectBoundary.left + rectBoundary.right) / 2 + 65 + 20) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 12 + 88) + rectBoundary.top
		};
		Polygon(hdcmem, o, 3);

		if (OpenSndEfct == 1)SelectObject(hdcmem, hBrushOptionOne);
		else SelectObject(hdcmem, hBrushOptionTwo);

		POINT p[3] = { ((rectBoundary.left + rectBoundary.right) / 2 + 65 - 35) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 128) + rectBoundary.top,
			((rectBoundary.left + rectBoundary.right) / 2 + 65 - 15) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 - 13 + 128) + rectBoundary.top,
			((rectBoundary.left + rectBoundary.right) / 2 + 65 - 15) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 12 + 128) + rectBoundary.top
		};
		Polygon(hdcmem, p, 3);
		if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
		{
			CHAR szSourceInfo[1024];
			switch (OpenSndEfct)
			{
			case 1:
				wsprintf(szSourceInfo, "��");
				break;
			case 0:
				wsprintf(szSourceInfo, "��");
				break;
			default:
				break;
			}
			// ���������ɫ
			SetTextColor(hdcmem, COLOR_TEXT);
			//�������屳��͸��
			SetBkMode(hdcmem, TRANSPARENT);
			// ����ַ�����
			TextOut(hdcmem, (rectBoundary.left + rectBoundary.right) / 2 + 65, (rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 120,
				szSourceInfo, lstrlen(szSourceInfo));
			// �����ɣ���ԭ�����������Ż�DC��
			SelectObject(hdcmem, hOldFont);
		}
		if (OpenSndEfct == 0)SelectObject(hdcmem, hBrushOptionOne);
		else SelectObject(hdcmem, hBrushOptionTwo);
		POINT q[3] = { ((rectBoundary.left + rectBoundary.right) / 2 + 65 + 40) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 128) + rectBoundary.top,
			((rectBoundary.left + rectBoundary.right) / 2 + 65 + 20) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 - 13 + 128) + rectBoundary.top,
			((rectBoundary.left + rectBoundary.right) / 2 + 65 + 20) + rectBoundary.left,((rectBoundary.bottom + rectBoundary.top) / 2 - 100 + 12 + 128) + rectBoundary.top
		};
		Polygon(hdcmem, q, 3);

	BitBlt(hdc,
		0, 0, rect.right - rect.left, rect.bottom - rect.top,
		hdcmem, 0, 0, SRCCOPY);

	DeleteObject(hbmMem);
	DeleteObject(HBG1);
	DeleteObject(hdcmem);
	DeleteObject(hpen);
	DeleteObject(hPenBoundary);
	DeleteObject(hFont);
	DeleteObject(hOldBrush);
	DeleteObject(hOldPen);
	DeleteObject(hOldFont);
	DeleteObject(hBrushOptionOne);
	DeleteObject(hBrushOptionTwo);
	DeleteObject(hBrushBackground);
	DeleteDC(hdcmem);
	ReleaseDC(hwnd, hdc);
}

LONG CALLBACK MainWndProc(
	HWND hwnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	static BOOL ColorAvr = 1;//�����ֶ�ƽ��ʱ����
	switch(msg)
	{
	    case WM_CREATE:
			CreateMain(hwnd, 300, 600);
			ReSizeGameWnd(hwnd);
			//Bg(hwnd);//���뱳��
			break;
		case WM_KEYDOWN:
			OnKeyDown(wParam,hwnd);
			break;
		case WM_KEYUP:
			OnKeyUp(wParam, hwnd);
			break;
		case WM_DESTROY://������Ͻǲ�棬���׹رճ��򣬲�д�ز���
			ExitProcess(0);
			break;
		case WM_PAINT:
			if (page <= MainPage3)
			{
				MainPaint(hwnd);
			}
			else if (page <= GamePage)
			{
				GamePaint(hwnd);
			}
			else
			{
				OptionPaint(hwnd);
			}

			
			break;
		case WM_TIMER:
			if (RightPress)MoveRBall();
			if (LeftPress)MoveLBall();
			//if (RightPress)MoveRBall();
			
			
			OnTimer(hwnd);//��ʱ��������������
			if (isGameOver())
			{
				if (OpenMusic)
				{
					//
					CreateThread(NULL, 0, PlayGameOver, NULL, 0, NULL);
				}
				KillTimer(hwnd, 12340);
				MessageBox(hwnd, "Game Over", "Oops!", MB_OK);
				CreateThread(NULL, 0, StopMusic, NULL, 0, NULL);
				Destory();
				page = MainPage1;
				MainPaint(hwnd);
			}
			else
			{
				GamePaint(hwnd);
			}
			
			BoardColor = RGB(255, 236 - ChangeColor * 3, 124 - ChangeColor * 3);
			if(OpenMusic)ChangeColor+=1;
			else ChangeColor = 0;
			if (ChangeColor >= 30 + ColorAvr)
			{
				ChangeColor = 1;
				ColorAvr = !ColorAvr;
			}
			//if (GetAM())ChangeColor += 0.5;
			//GamePaint(hwnd);
			/*KillTimer(hwnd, 12340);
			MessageBox(hwnd, "f*CK", "SHIT", MB_OK| MB_OKCANCEL);
			page = MainPage3;
			MainPaint(hwnd);*/
			break;
		default:
			break;
	}
	return DefWindowProc(hwnd,msg,wParam,lParam);
}
void OnKeyDown(WPARAM P,HWND hwnd)
{
	switch (P) {
	case VK_UP:
		switch (page) {
		case MainPage1:
			page = MainPage3;
			MainPaint(hwnd);
			break;
		case MainPage2:
			page = MainPage1;
			MainPaint(hwnd);
			break;
		case MainPage3:
			page = MainPage2;
			MainPaint(hwnd);
			break;
		case OptionPage1:
			page = OptionPage5;
			OptionPaint(hwnd);
			break;
		case OptionPage2:
			page = OptionPage1;
			OptionPaint(hwnd);
			break;
		case OptionPage3:
			page = OptionPage2;
			OptionPaint(hwnd);
			break;
		case OptionPage4:
			page = OptionPage3;
			OptionPaint(hwnd);
			break;
		case OptionPage5:
			page = OptionPage4;
			OptionPaint(hwnd);
			break;
		default:
			break;
		}
		break;
	case VK_DOWN:
		switch (page) {
		case MainPage1:
			page = MainPage2;
			MainPaint(hwnd);
			break;
		case MainPage2:
			page = MainPage3;
			MainPaint(hwnd);
			break;
		case MainPage3:
			page = MainPage1;
			MainPaint(hwnd);
			break;
		case OptionPage1:
			page = OptionPage2;
			OptionPaint(hwnd);
			break;
		case OptionPage2:
			page = OptionPage3;
			OptionPaint(hwnd);
			break;
		case OptionPage3:
			page = OptionPage4;
			OptionPaint(hwnd);
			break;
		case OptionPage4:
			page = OptionPage5;
			OptionPaint(hwnd);
			break;
		case OptionPage5:
			page = OptionPage1;
			OptionPaint(hwnd);
			break;
		default:
			break;
		}
		break;
	case VK_RETURN:
		switch (page) {
		case MainPage1:
			CreateGame(hwnd, Color, Diffculty, ballType,OpenMusic,OpenSndEfct,hwnd);
			LeftPress = FALSE;
			RightPress = FALSE;
			page = GamePage;
			GamePaint(hwnd);
			
			break;
		case MainPage2:
			page = OptionPage1;
			OptionPaint(hwnd);
			break;
		case OptionPage5:
			page = MainPage1;
			MainPaint(hwnd);
			break;
		case MainPage3:
			ExitProcess(0);
			break;
		default:
			break;
		}
		break;
	case VK_LEFT:
		switch (page)
		{
		case GamePage:
			LeftPress = TRUE;
			//MoveLBall();
			//GamePaint(hwnd);
			break;
		case OptionPage1:
			if (Diffculty - 1>=0)Diffculty--;
			OptionPaint(hwnd);
			break;
		case OptionPage2:
			if (ballType !=Light)ballType--;
			OptionPaint(hwnd);
			break;
		case OptionPage3:
			if (OpenMusic != 1)OpenMusic = 1;
			OptionPaint(hwnd);
			break;
		case OptionPage4:
			if (OpenSndEfct != 1)OpenSndEfct = 1;
			OptionPaint(hwnd);
			break;
		default:
			break;
		}
		break;
	case VK_RIGHT:
		switch (page)
		{
		case GamePage:
			RightPress = TRUE;
			//MoveRBall();
			//GamePaint(hwnd);
			break;
		case OptionPage1:
			if(Diffculty+1<3)Diffculty++;
			OptionPaint(hwnd);
			break;
		case OptionPage2:
			if (ballType != Heavy)ballType++;
			OptionPaint(hwnd);
			break;
		case OptionPage3:
			if (OpenMusic != 0)OpenMusic = 0;
			OptionPaint(hwnd);
			break;
		case OptionPage4:
			if (OpenSndEfct != 0)OpenSndEfct = 0;
			OptionPaint(hwnd);
			break;
		default:
			break;
		}
		break;
	case VK_SPACE:
		if (page == GamePage)
		{
			if (!TimeStop)
			{
				SetTimer(hwnd, 12340, 100000, NULL);
				TimeStop =TRUE;
			}
			else
			{
				TimeStop = FALSE;
				SetTimer(hwnd, 12340,10, NULL);
			}
		}
		break;
	default:
		break;
	}
	//MessageBox(hwnd,"f*CK","SHIT",MB_OK);
	//if (page == MainPage2) { SetTimer(hwnd, 12340, 300, NULL); }
}
void OnKeyUp(WPARAM P, HWND hwnd)
{
	switch (page)
	{
	case GamePage:
		switch (P)
		{
		case VK_LEFT:
			LeftPress = FALSE;
			break;
		case VK_RIGHT:
			RightPress = FALSE;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}







void ReSizeGameWnd(HWND hwnd)
{
	POINT ptLeftTop;		// ���Ͻ�
	POINT ptRightBottom;	// ���½�
	RECT rectWindow;
	PGAME_COORD pCoordBoundary = GetBoundary();

	// ������Ϸ�߽�
	rectBoundary.left = 10;
	rectBoundary.top = 10;
	rectBoundary.right = 10 + CELL_PIXEL*(pCoordBoundary->x + 1);
	rectBoundary.bottom =  10+CELL_PIXEL*(pCoordBoundary->y + 1);

	// �����������ҽǵ�λ��
	ptLeftTop.x = rectBoundary.left;
	ptLeftTop.y = rectBoundary.top;
	ptRightBottom.x = rectBoundary.right;
	ptRightBottom.y = rectBoundary.bottom;
	ClientToScreen(hwnd, &ptLeftTop);
	ClientToScreen(hwnd, &ptRightBottom);

	GetWindowRect(hwnd, &rectWindow);
	// ������ˣ����ô��ڴ�С��
	//MoveWindow(hwnd,
	//	0,
	//	0,
	//	ptLeftTop.x - rectWindow.left + ptRightBottom.x - rectWindow.left, // ����߽���������߱߿���ȡ�
	//	rectBoundary.bottom+80, //��������Ϣ������ʾ�ռ䡣
	//	TRUE);
}
LONG Bg(HWND hwnd)
{
	//HBG1= LoadImage(NULL, "title.bmp",
	//	IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//
	//if (HBG1 == NULL)
	//{
	//	MessageBox(hwnd, "bmp file not find", "ERROR!",
	//		MB_OK | MB_ICONERROR);
	//	//ExitProcess(0);
	//}
	//SetFocus(hwnd);
	return 0;
}

