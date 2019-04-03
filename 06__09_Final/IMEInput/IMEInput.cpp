// IMEInput.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "IMEInput.h"
#include "stdlib.h"
#include "stdio.h"
#include <gl\gl.h>
#include <gl\glu.h>
#include "Joystick\joystick.h"
#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


//	=============================================================================================
// Palette Handle
HPALETTE hPalette = NULL;


static LPCTSTR lpszAppName = _T("Text3D");
GLint nFontList;

// Light values and coordinates
GLfloat  whiteLight[] = { 0.4f, 0.4f, 0.4f, 1.0f };
GLfloat  diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat  specular[] = { 0.9f, 0.9f, 0.9f, 1.0f};
GLfloat lightPos[] = { -100.0f, 200.0f, 50.0f, 1.0f };
//	=============================================================================================

void ChangeSize(GLsizei w, GLsizei h) {
	GLfloat nRange = 100.0f;
	GLfloat fAspect;

	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	fAspect = (GLfloat)w/(GLfloat)h;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);

	// Reset coordinate system
	glLoadIdentity();

	// Setup perspective for viewing
	gluPerspective(17.5f,fAspect,1,300);

	// Viewing transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-1.8f, 0.0f, -15.0f);
	glRotatef(-20.0f, 0.0f, 1.0f,0.0f);

	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

	//GLfloat nRange = 100.0f;
	//GLfloat fAspect;

	//// Prevent a divide by zero
	//if(h == 0)
	//	h = 1;

	//fAspect = (GLfloat)w/(GLfloat)h;

	//// Set Viewport to window dimensions
	//glViewport(0, 0, w, h);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	//gluOrtho2D(0,400, 400, 0);

	//// Viewing transformation
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
}

TCHAR strBuffer[1024] = _T("OpenGL中文");
unsigned int strLength = 8;

void InputChar(TCHAR chr) {
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Blue 3D Text
	glColor3ub(0, 0, 255);

	glPushMatrix();

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//// Blue 3D Text	- Note color is set before the raster position
	//glColor3f(1.0f, 1.0f, 1.0f);
	//glRasterPos2i(0, 200);

	for (unsigned int i1 = 0 ; i1 < strLength ; i1 ++ ) {
		glListBase(1000 + i1);
		glCallLists (1, GL_UNSIGNED_SHORT, _T("\0")); 	
	}

	glPopMatrix();
}

GLYPHMETRICSFLOAT agmf[65536]; // Throw away

void SetupRC(HDC hDC) {
	// Setup the Font characteristics
	HFONT hFont;
	LOGFONT logfont;

	logfont.lfHeight = -39;
	logfont.lfWidth = 29;
	logfont.lfEscapement = 0;
	logfont.lfOrientation = 0;
	logfont.lfWeight = FW_BOLD;
	logfont.lfItalic = FALSE;
	logfont.lfUnderline = FALSE;
	logfont.lfStrikeOut = FALSE;
	logfont.lfCharSet = ANSI_CHARSET;
	logfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logfont.lfQuality = DEFAULT_QUALITY;
	logfont.lfPitchAndFamily = DEFAULT_PITCH;
	_tcscpy(logfont.lfFaceName,_T("liguofu"));
	//wcscpy(logfont.lfFaceName,L"新宋体");

	// Create the font and display list
	hFont = CreateFontIndirect(&logfont);
	SelectObject (hDC, hFont); 


	//create display lists for glyphs 0 through 128 with 0.1 extrusion 
	// and default deviation. 
	//	nFontList = glGenLists(65535);

	//wglUseFontBitmapsW(hDC, 0, 128, 1000);
	//wglUseFontBitmapsW(hDC, (L"中")[0], 1, 1001);
	//wglUseFontBitmapsW(hDC, (L"文")[0], 1, 1002);
	//for (unsigned int i1 = 0 ; i1 < strLength ; i1 ++ ) {
	//	wglUseFontBitmaps(hDC, strBuffer[i1], 1, 1000 + i1); 
	//}

	//wglUseFontOutlines(hDC, 0, 128, 1000, 0.0f, 0.5f, WGL_FONT_POLYGONS, agmf); 
	//wglUseFontOutlines(hDC, _T("中")[0], 1, 1001, 0.0f, 0.5f, WGL_FONT_POLYGONS, agmf); 
	//wglUseFontOutlines(hDC, _T("文")[0], 1, 1002, 0.0f, 0.5f, WGL_FONT_POLYGONS, agmf); 
	for (unsigned int i1 = 0 ; i1 < strLength ; i1 ++ ) {
		wglUseFontOutlines(hDC, strBuffer[i1], 1, 1000 + i1, 0.0f, 0.5f, WGL_FONT_POLYGONS, agmf); 
	}

	DeleteObject(hFont);

	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0,GL_AMBIENT,whiteLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHT0);


	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR,specular);
	glMateriali(GL_FRONT,GL_SHININESS,128);
}


// If necessary, creates a 3-3-2 palette for the device context listed.
HPALETTE GetOpenGLPalette(HDC hDC) {
	HPALETTE hRetPal = NULL;	// Handle to palette to be created
	PIXELFORMATDESCRIPTOR pfd;	// Pixel Format Descriptor
	LOGPALETTE *pPal;			// Pointer to memory for logical palette
	int nPixelFormat;			// Pixel format index
	int nColors;				// Number of entries in palette
	int i;						// Counting variable
	BYTE RedRange,GreenRange,BlueRange;
								// Range for each color entry (7,7,and 3)


	// Get the pixel format index and retrieve the pixel format description
	nPixelFormat = GetPixelFormat(hDC);
	DescribePixelFormat(hDC, nPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	// Does this pixel format require a palette?  If not, do not create a
	// palette and just return NULL
	if(!(pfd.dwFlags & PFD_NEED_PALETTE))
		return NULL;

	// Number of entries in palette.  8 bits yeilds 256 entries
	nColors = 1 << pfd.cColorBits;	

	// Allocate space for a logical palette structure plus all the palette entries
	pPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) +nColors*sizeof(PALETTEENTRY));

	// Fill in palette header 
	pPal->palVersion = 0x300;		// Windows 3.0
	pPal->palNumEntries = nColors; // table size

	// Build mask of all 1's.  This creates a number represented by having
	// the low order x bits set, where x = pfd.cRedBits, pfd.cGreenBits, and
	// pfd.cBlueBits.  
	RedRange = (1 << pfd.cRedBits) -1;
	GreenRange = (1 << pfd.cGreenBits) - 1;
	BlueRange = (1 << pfd.cBlueBits) -1;

	// Loop through all the palette entries
	for(i = 0; i < nColors; i++) {
		// Fill in the 8-bit equivalents for each component
		pPal->palPalEntry[i].peRed = (i >> pfd.cRedShift) & RedRange;
		pPal->palPalEntry[i].peRed = (unsigned char)(
			(double) pPal->palPalEntry[i].peRed * 255.0 / RedRange);

		pPal->palPalEntry[i].peGreen = (i >> pfd.cGreenShift) & GreenRange;
		pPal->palPalEntry[i].peGreen = (unsigned char)(
			(double)pPal->palPalEntry[i].peGreen * 255.0 / GreenRange);

		pPal->palPalEntry[i].peBlue = (i >> pfd.cBlueShift) & BlueRange;
		pPal->palPalEntry[i].peBlue = (unsigned char)(
			(double)pPal->palPalEntry[i].peBlue * 255.0 / BlueRange);

		pPal->palPalEntry[i].peFlags = (unsigned char) NULL;
	}
		

	// Create the palette
	hRetPal = CreatePalette(pPal);

	// Go ahead and select and realize the palette for this device context
	SelectPalette(hDC,hRetPal,FALSE);
	RealizePalette(hDC);

	// Free the memory used for the logical palette structure
	free(pPal);

	// Return the handle to the new palette
	return hRetPal;
}


// Select the pixel format for a given device context
void SetDCPixelFormat(HDC hDC) {
	int nPixelFormat;

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),	// Size of this structure
		1,								// Version of this structure	
		PFD_DRAW_TO_WINDOW |			// Draw to Window (not to bitmap)
		PFD_SUPPORT_OPENGL |			// Support OpenGL calls in window
		PFD_DOUBLEBUFFER,				// Double buffered mode
		PFD_TYPE_RGBA,					// RGBA Color mode
		32,								// Want 32 bit color
		0,0,0,0,0,0,					// Not used to select mode
		0,0,							// Not used to select mode
		0,0,0,0,0,						// Not used to select mode
		16,								// Size of depth buffer
		0,								// Not used to select mode
		0,								// Not used to select mode
		0,								// Draw in main plane
		0,								// Not used to select mode
		0,0,0 };						// Not used to select mode

	// Choose a pixel format that best matches that described in pfd
	nPixelFormat = ChoosePixelFormat(hDC, &pfd);

	// Set the pixel format for the device context
	SetPixelFormat(hDC, nPixelFormat, &pfd);
}




int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 //	// TODO: 在此放置代码。
	//MSG msg;
	//HACCEL hAccelTable;

	//// 初始化全局字符串
	//LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	//LoadString(hInstance, IDC_IMEINPUT, szWindowClass, MAX_LOADSTRING);
	//MyRegisterClass(hInstance);

	//// 执行应用程序初始化:
	//if (!InitInstance (hInstance, nCmdShow)) 
	//{
	//	return FALSE;
	//}

	//hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_IMEINPUT);

	//// 主消息循环:
	//while (GetMessage(&msg, NULL, 0, 0)) 
	//{
	//	if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
	//	{
	//		TranslateMessage(&msg);
	//		DispatchMessage(&msg);
	//	}
	//}

	//return (int) msg.wParam;


	//MSG			msg;		// Windows message structure
	//WNDCLASS	wc;			// Windows class structure
	//HWND		hWnd;		// Storeage for window handle


	//// Register Window style
	//wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	//wc.lpfnWndProc		= (WNDPROC) WndProc;
	//wc.cbClsExtra		= 0;
	//wc.cbWndExtra		= 0;
	//wc.hInstance 		= hInstance;
	//wc.hIcon			= NULL;
	//wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	//
	//// No need for background brush for OpenGL window
	//wc.hbrBackground	= NULL;		
	//
	//wc.lpszMenuName		= NULL;
	//wc.lpszClassName	= lpszAppName;

	//// Register the window class
	//if(RegisterClass(&wc) == 0)
	//	return FALSE;


	//// Create the main application window
	//hWnd = CreateWindow(
	//			lpszAppName,
	//			lpszAppName,
	//			
	//			// OpenGL requires WS_CLIPCHILDREN and WS_CLIPSIBLINGS
	//			WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
	//
	//			// Window position and size
	//			100, 100,
	//			250, 250,
	//			NULL,
	//			NULL,
	//			hInstance,
	//			NULL);

	//// If window was not created, quit
	//if(hWnd == NULL)
	//	return FALSE;


	//// Display the window
	//ShowWindow(hWnd,SW_SHOW);
	//UpdateWindow(hWnd);

	//// Process application messages until the application closes
	//while( GetMessage(&msg, NULL, 0, 0))
	//	{
	//	TranslateMessage(&msg);
	//	DispatchMessage(&msg);
	//	}

	//return (int)msg.wParam;

	MSG			msg;		// Windows message structure
	WNDCLASS	wc;			// Windows class structure
	HWND		hWnd;		// Storeage for window handle
	HWND		hDesktopWnd;// Storeage for desktop window handle
	HDC			hDesktopDC; // Storeage for desktop window device context
	int			nScreenX, nScreenY; // Screen Dimensions

	// Register Window style
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= (WNDPROC) WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance 		= hInstance;
	wc.hIcon			= NULL;
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	
	// No need for background brush for OpenGL window
	wc.hbrBackground	= NULL;		
	
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= lpszAppName;

	// Register the window class
	if(RegisterClass(&wc) == 0)
		return FALSE;

    // Get he Window handle and Device context to the desktop
	hDesktopWnd = GetDesktopWindow();
	hDesktopDC = GetDC(hDesktopWnd);

    // Get the screen size
	nScreenX = GetDeviceCaps(hDesktopDC, HORZRES);
	nScreenY = GetDeviceCaps(hDesktopDC, VERTRES);

    // Release the desktop device context
    ReleaseDC(hDesktopWnd, hDesktopDC);

	// Create the main application window
	hWnd = CreateWindow(
				lpszAppName,
				lpszAppName,
				
				// OpenGL requires WS_CLIPCHILDREN and WS_CLIPSIBLINGS
				WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
	
				// Window position and size
				0, 0,
				nScreenX, nScreenY,
				NULL,
				NULL,
				hInstance,
				NULL);


	// If window was not created, quit
	if(hWnd == NULL)
		return FALSE;


	// Display the window
	ShowWindow(hWnd,SW_SHOW);
	UpdateWindow(hWnd);

	// Process application messages until the application closes
	while( GetMessage(&msg, NULL, 0, 0))
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}

	return (int)msg.wParam;

}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释: 
//
//    仅当希望在已添加到 Windows 95 的
//    “RegisterClassEx”函数之前此代码与 Win32 系统兼容时，
//    才需要此函数及其用法。调用此函数
//    十分重要，这样应用程序就可以获得关联的
//   “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_IMEINPUT);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCTSTR)IDC_IMEINPUT;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HANDLE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd) {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

Joystick* joysticks[4];
unsigned int numJoysticks = Joystick::deviceCount();

//
//  函数: WndProc(HWND, unsigned, WORD, LONG)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	//int wmId, wmEvent;
	//PAINTSTRUCT ps;
	//HDC hdc;

	//switch (message) 
	//{
	//case WM_COMMAND:
	//	wmId    = LOWORD(wParam); 
	//	wmEvent = HIWORD(wParam); 
	//	// 分析菜单选择:
	//	switch (wmId)
	//	{
	//	case IDM_ABOUT:
	//		DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
	//		break;
	//	case IDM_EXIT:
	//		DestroyWindow(hWnd);
	//		break;
	//	default:
	//		return DefWindowProc(hWnd, message, wParam, lParam);
	//	}
	//	break;
	//case WM_PAINT:
	//	hdc = BeginPaint(hWnd, &ps);
	//	// TODO: 在此添加任意绘图代码...
	//	EndPaint(hWnd, &ps);
	//	break;
	//case WM_DESTROY:
	//	PostQuitMessage(0);
	//	break;
	//case WM_CHAR:
	//	{
	//		TCHAR buf[128];
	//		_stprintf(buf, _T("u%4X"), wParam);
	//		MessageBox(hWnd, buf, _T("Code"), 0);
	//	}
	//	break;
	//default:
	//	return DefWindowProc(hWnd, message, wParam, lParam);
	//}
	//return 0;
	static HGLRC hRC;		// Permenant Rendering context
	static HDC hDC;			// Private GDI Device context

	switch (message) {
	// Window creation, setup for OpenGL
	case WM_CREATE:
		// Store the device context
		hDC = GetDC(hWnd);		

		// Select the pixel format
		SetDCPixelFormat(hDC);		

		// Create the rendering context and make it current
		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);

		// Create the palette
		hPalette = GetOpenGLPalette(hDC);

		SetupRC(hDC);
		//if(joySetCapture(hWnd, JOYSTICKID1, NULL, FALSE)) { 
		//	MessageBox(hWnd, _T("Couldn't capture the joystick."), NULL, MB_OK | MB_ICONEXCLAMATION); 
		//} 
		for (unsigned int i = 0; i < numJoysticks; i++) {
			joysticks[i] = new Joystick(i);
			joysticks[i]->open();

			// Print the name of the joystick.
			TCHAR name[MAX_PATH];
			joysticks[i]->deviceName(name);
			//printf("  Joystick %d: %s\n", i, name);
		}

		break;

	// Window is being destroyed, cleanup
	case WM_DESTROY:
		// Kill the timer that we created
		KillTimer(hWnd,101);

		glDeleteLists(nFontList, 128);

		// Deselect the current rendering context and delete it
		wglMakeCurrent(hDC,NULL);
		wglDeleteContext(hRC);

		// Delete the palette
		if(hPalette != NULL)
			DeleteObject(hPalette);

		// Tell the application to terminate after the window
		// is gone.
		PostQuitMessage(0);
		break;

	// Window is resized.
	case WM_SIZE:
		// Call our function which modifies the clipping
		// volume and viewport
		ChangeSize(LOWORD(lParam), HIWORD(lParam));
		break;

		// The painting function.  This message sent by Windows 
		// whenever the screen needs updating.
		case WM_PAINT:
		{
			// Call OpenGL drawing code
			RenderScene();

			// Call function to swap the buffers
			SwapBuffers(hDC);

			ValidateRect(hWnd,NULL);
		}
		break;


	// Windows is telling the application that it may modify
	// the system palette.  This message in essance asks the 
	// application for a new palette.
	case WM_QUERYNEWPALETTE:
		// If the palette was created.
		if(hPalette) {
			int nRet;

			// Selects the palette into the current device context
			SelectPalette(hDC, hPalette, FALSE);

			// Map entries from the currently selected palette to
			// the system palette.  The return value is the number 
			// of palette entries modified.
			nRet = RealizePalette(hDC);

			// Repaint, forces remap of palette in current window
			InvalidateRect(hWnd,NULL,FALSE);

			return nRet;
		}
		break;


	// This window may set the palette, even though it is not the 
	// currently active window.
	case WM_PALETTECHANGED:
		// Don't do anything if the palette does not exist, or if
		// this is the window that changed the palette.
		if((hPalette != NULL) && ((HWND)wParam != hWnd)) {
			// Select the palette into the device context
			SelectPalette(hDC,hPalette,FALSE);

			// Map entries to system palette
			RealizePalette(hDC);

			// Remap the current colors to the newly realized palette
			UpdateColors(hDC);
			return 0;
		}
		break;

	case WM_CHAR:
		{
			strBuffer[strLength++] = (TCHAR)wParam;
			strBuffer[strLength] = 0;

			hDC = GetDC(hWnd);		
			SetupRC(hDC);
			RenderScene();
			SwapBuffers(hDC);
			ValidateRect(hWnd,NULL);
		}
		break;

	case WM_KEYDOWN:
		{
			if ( GetAsyncKeyState(VK_RETURN) < 0 ) {

			} else if ( GetAsyncKeyState(VK_DELETE) < 0 ) {
				strLength = 0;

				hDC = GetDC(hWnd);		
				SetupRC(hDC);
				RenderScene();
				SwapBuffers(hDC);
				ValidateRect(hWnd,NULL);
			}
			DIJOYSTATE2 js;

//			joysticks[0]->poll(&js);

		}
		break;
	//case MM_JOY1MOVE:
	//	{
	//		//MessageBox(hWnd, _T("MM_JOY1MOVE"), _T("Code"), 0);
	//	}
	//	break;
	//case MM_JOY1ZMOVE:
	//	{
	//		//MessageBox(hWnd, _T("MM_JOY1ZMOVE"), _T("Code"), 0);
	//	}
	//	break;
	//case MM_JOY1BUTTONDOWN:
	//	{
	//		MessageBox(hWnd, _T("MM_JOY1BUTTONDOWN"), _T("Code"), 0);
	//	}
	//	break;
	//case MM_JOY1BUTTONUP:
	//	{
	//		MessageBox(hWnd, _T("MM_JOY1BUTTONUP"), _T("Code"), 0);
	//	}
	//	break;
	default:   // Passes it on if unproccessed
		return (DefWindowProc(hWnd, message, wParam, lParam));

	}

	return (0L);
}

// “关于”框的消息处理程序。
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}
