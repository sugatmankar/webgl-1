#include<Windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
bool gbDone = false;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLIne, int iCmdShow){
	WNDCLASSEX wndclass;
	TCHAR AppName[] = TEXT("Window Custom");
	TCHAR WinName[] = TEXT("Window At Centre");
	HWND hwnd;
	MSG msg;
	RECT rect;
	//initialize window class
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = AppName;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	//initialization complete
	
	RegisterClassEx(&wndclass); //Register Class
	
	SystemParametersInfo(SPI_GETWORKAREA,0,&rect,0);
	int width = (rect.right-rect.left)/2 - WIN_WIDTH/2;
	int height = (rect.bottom - rect.top)/2 - WIN_HEIGHT/2;
	//int width = GetSystemMetrics(SM_CXSCREEN)/2 - WIN_WIDTH/2;
	//int height = GetSystemMetrics(SM_CYSCREEN)/2 - WIN_HEIGHT/2;
	//create window in memory
	hwnd = CreateWindow(
	AppName,
	WinName,
	WS_OVERLAPPEDWINDOW,
	width,
	height,
	WIN_WIDTH,
	WIN_HEIGHT,
	NULL,
	NULL,
	hInstance,
	NULL
	);
	
	ShowWindow(hwnd, iCmdShow); //Show Window
	//ShowWindow(hwnd, SW_MAXIMIZE); //Show Window
	UpdateWindow(hwnd); // color/paint the background of the window
	
	//message loop
	while(gbDone==false){
		
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if(msg.message == WM_QUIT){
				gbDone = true;
			}else{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}else{
			//rendering starts here
		}
	}
	return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam){
	TCHAR str[255];
	int xPos;
	int yPos;
	switch(iMsg){
		
		case WM_CREATE:
			wsprintf(str,TEXT("Message From Create Window"));
			MessageBox(NULL,str,TEXT("To Rohit"),MB_OK);
		break;
		case WM_LBUTTONDOWN:
			 xPos = LOWORD(lParam);
			 yPos = HIWORD(lParam);
			wsprintf(str,TEXT("You clicked at x-%d and y-%d"),xPos,yPos);
			MessageBox(NULL,str,TEXT("To Rohit"),MB_OK);
		break;
		case WM_KEYDOWN:
			switch(LOWORD(wParam)){
				case VK_ESCAPE:
				wsprintf(str,TEXT("Escape Key is pressed"));
				MessageBox(NULL,str,TEXT("To Rohit"),MB_OK);
				break;
				case 0x41:
				wsprintf(str, TEXT("A key is pressed"));
				MessageBox(hwnd, str, TEXT("Key Identified as"),MB_OK);
				break;
				case 0x42:
				wsprintf(str, TEXT("B key is pressed"));
				MessageBox(hwnd, str, TEXT("Key Identified as"),MB_OK);
				break;
				case 0x46:
				wsprintf(str,TEXT("F key is pressed."));
				MessageBox(hwnd,str,TEXT("Key Identified as"),MB_OK);
				break;
				case 0x4C:
					wsprintf(str, TEXT("L key is pressed"));
					MessageBox(hwnd, str, TEXT("Key Identified as"),MB_OK);
					break;
				case 0x54:
					wsprintf(str,TEXT("T key is pressed"));
					MessageBox(hwnd,str,TEXT("Key Identified as"),MB_OK);
					break;
				case 0x51:
					wsprintf(str,TEXT("Q key is pressed"));
					MessageBox(hwnd,str,TEXT("Key Identified as"),MB_OK);
					break;
			}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}