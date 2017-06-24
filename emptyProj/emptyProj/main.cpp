#include <Windows.h>
#include <tchar.h>
#include <stdlib.h>  
#include <string.h> 
//Global variables here

//the main window class name
static TCHAR szWindowClass[] = _T("sup_holmes"); //TCHAR is just a 'char' typedef

//the string that appears in the application's title bar
static TCHAR szTitle[] = _T("I am teh title bar");

static HINSTANCE hInst;

// Forward declarations of functions included in this code module:  
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
	HINSTANCE hInstance,/*handle to the current instance, this program*/
	HINSTANCE hPrevInstance,/*A handle to the previous instance of the application,*/
	LPSTR		lpCmdLine, /*The command line for the application*/
	int nCmdShow /*how the window is to be shown*/
)
{
	//uncomment the below code for a simple message box
	/*MessageBox(NULL, "Hello", "My first gui", MB_OK);*/

	//create a windows class - look up online 'WNDCLASSEX' for its funcationality in detail
	//it does alot of shit for you windows like background color, size ect. 
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	//NOW, You must register the WNDCLASSEX with Windows so that it knows about your window and how to send messages to it.
	//RegisterClassEx will return 0 if it couldnt register the windows with Windows 10 OS 
	if (!RegisterClassEx(&wcex))
	{
		//if the registration failed
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows registration"),
			NULL);

		return 1;
	}
	//registration sucessful

	hInst = hInstance;// Store instance handle in our global variable  

	//now create a window 
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 100,
		NULL, 
		NULL, 
		hInstance, 
		NULL);

	//if creating a window failed
	if (!hWnd)
	{
		//Winows Creation had failed
		MessageBox(NULL,
			_T("Called to 'CreateWindow()' had failed "),
			_T("Failed the Windows creation"),
			NULL);
		return 1;
	}
	//windows creations was succesful 

	// The parameters to ShowWindow explained:  
	// hWnd: the value returned from CreateWindow  
	// nCmdShow: the fourth parameter from WinMain  
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	//so far 1. we registered a windows class, 2. created a window
		//now lets  remember that litereal 'windows' on windowsOS, persist on screen until user/program terminates it. Before termination, it persists in a LOOP (i used a while loop)
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;

}
//this is the part of the progam that does YOUR code
//add buttons, functions, ect in the LRESULT body 
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Ryans a fegget >:D");

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Here your application is laid out.  
		// For this introduction, we just print out "Hello, World!"  
		// in the top left corner.  
		TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));
		// End application-specific layout section.  

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}