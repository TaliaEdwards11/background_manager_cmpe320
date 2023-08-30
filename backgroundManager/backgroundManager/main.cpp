// main.cpp
// can compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c
// this is a traditional windows desktop app 
// it allows for more permissions regarding files + windows api
// the base of this app was create using a Windows tutorial to print hello world

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <iostream>
#include "atlbase.h"
#include "atlstr.h"
#include "comutil.h"
#include <vector>
#include <time.h>
#include <fstream>
#include <ctime>
#include "backgroundSetter.h"
#include "UserInformation.h"
#include "PastImages.h"


// define the ids for textbox, windows and buttons
#define id_default_menu 0
#define id_interest_menu 1
#define id_exit_menu 2
#define id_setting_menu 3
#define bgChanger_id 4
#define bgText_id 5
#define interest_id 6
#define enter_id 7
#define back_id 8
#define name_id 9
#define submit_id 10
#define skip_id 11
#define bd_id 12
#define weather_id 13
#define holiday_id 14
#define update_bd_id 15
#define update_weather_id 16
#define update_holiday_id 17
#define interest_generator_id 18
#define current_bg_id 19
#define del_current_bg_id 20
#define favourite_bg_id 21




using namespace std;


// declare functions 
//int changeBackground(const wchar_t* imagePath);
void addMenus();
string wchar_to_string(wchar_t* str);
string generateInterest();
void retrieveImage(string searchTerms);
void reverseRetrieveImage(string filepath);


// windows for main, setting and interest page 
HMENU hMenu;
HWND hWnd;
HWND hWnd2;
HWND hWnd3;

// start at main page 
// winNum holds the current window that is being created or displayed 
int winNum = id_default_menu;


// main window class name
static TCHAR szWindowClass[] = _T("DesktopApp");

// app title bar
static TCHAR szTitle[] = _T("Background Manager");

HINSTANCE hInst;

// declarating functions
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	// structure contains a function pointer to the windows procedure 
	// info about the window (bg color, icon, etc.)
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = reinterpret_cast<HICON>(LoadImage(nullptr, L"backgroundconfig.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE));;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = reinterpret_cast<HICON>(LoadImage(nullptr, L"backgroundconfig.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE));

	//register class so windows knows about it
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Background Manager"),
			NULL);

		return 1;
	}

	// Store instance handle in our global variable
	hInst = hInstance;

	// The parameters to CreateWindowEx explained:
	// WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
	// szWindowClass: the name of the application
	// szTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
	// 500, 100: initial size (width, length)
	// NULL: the parent of this window
	// NULL: this application does not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application
	
	// create main window (BG manager window)
	hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		400, 350,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	// create interest window 
	winNum = id_interest_menu;
	hWnd2 = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 330,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	//create setting window
	winNum = id_setting_menu;
	hWnd3 = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 420,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	// if main failed make an error message
	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Background Manager"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	

	// Main message loop:
	
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
	
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return

// initialize textbox
static HWND textBox1;
static HWND textBox2;
static HWND textBox3;
static HWND textBox4;
static HWND textBox5;
// initialize label
static HWND label1, label2, label3, label4, label5, label6, label7, label8, label9, label10, label11, label12, label13;
// initialize font
static HFONT hFont, shFont, tFont;
// initialize button
static HWND button1, button2, button3, button4, button5, button6, button7, button8, button9, button10, button11, button12;

LRESULT CALLBACK WndProc(HWND curr, UINT message, WPARAM wParam, LPARAM lParam)
{
	// The first number represent the size of word
	// Font
	hFont = CreateFont(30, 0, 0, 0, FW_DONTCARE,
		FALSE, FALSE, FALSE,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, // FW_BOLD for Bold, 
		L"Impact"
	);
	shFont = CreateFont(25, 0, 0, 0, FW_DONTCARE,
		FALSE, FALSE, FALSE,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, // FW_BOLD for Bold, 
		L"Impact"
	);
	tFont = CreateFont(20, 0, 0, 0, FW_DONTCARE,
		FALSE, FALSE, FALSE,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, // FW_BOLD for Bold, 
		L"Impact"
	);
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Background Manager");
	//CStringW str = "C:\\users\\talia\\onedrive\\bureau\\mountBourgeau.jpg";
	//"C:\users\talia\onedrive\bureau\Neuschwanstein-Castle.jpg" mountBourgeau.jpg
	//"C:\users\talia\onedrive\bureau\mountBourgeau.jpg" 
	//const wchar_t* path = str.GetString();

	//Window controls 
	switch (message)
	{
	// Put what goes in the window here 
	// like buttons and textbox
	case WM_CREATE: {
		// create the menu for the main page 
		addMenus();
		// check winNum to find out which window is being created
		
			
		if (winNum == id_default_menu) {
			//hWnd2.hbrBackground = hb;
			// the numbers represent x position, y position, x width, y height
			// labels in default menu
			label1 = CreateWindow(TEXT("STATIC"), TEXT("Default Menu"),
				WS_VISIBLE | WS_CHILD | SS_CENTER,
				125, 25, 140, 25,
				curr, (HMENU)4, NULL, NULL
			);

			SendMessage(label1, WM_SETFONT, WPARAM(hFont), TRUE); // change font of label1
			// buttons in default menu
			button1 = CreateWindow(TEXT("BUTTON"), TEXT("Save Background to Favourites"),
				WS_VISIBLE | WS_CHILD,
				40, 60, 300, 25,
				curr, (HMENU)bgChanger_id, NULL, NULL
			);
			SendMessage(button1, WM_SETFONT, WPARAM(tFont), TRUE); // change font of button1

			button2 = CreateWindow(TEXT("BUTTON"), TEXT("Change Background"),
				WS_VISIBLE | WS_CHILD,
				40, 100, 300, 25,
				curr, (HMENU)skip_id, NULL, NULL
			);
			SendMessage(button2, WM_SETFONT, WPARAM(tFont), TRUE); // change font of button2
			button3 = CreateWindow(TEXT("BUTTON"), TEXT("Load Previous Backgrounds"),
				WS_VISIBLE | WS_CHILD,
				40, 140, 300, 25,
				curr, (HMENU)current_bg_id, NULL, NULL
			);
			SendMessage(button3, WM_SETFONT, WPARAM(tFont), TRUE); // change font of button3
			button4 = CreateWindow(TEXT("BUTTON"), TEXT("Load Favourite Backgrounds"),
				WS_VISIBLE | WS_CHILD,
				40, 180, 300, 25,
				curr, (HMENU)favourite_bg_id, NULL, NULL
			);
			SendMessage(button4, WM_SETFONT, WPARAM(tFont), TRUE); // change font of button4
			button5 = CreateWindow(TEXT("BUTTON"), TEXT("Delete from Previous Backgrounds"),
				WS_VISIBLE | WS_CHILD,
				40, 220, 300, 25,
				curr, (HMENU)del_current_bg_id, NULL, NULL
			);
			SendMessage(button5, WM_SETFONT, WPARAM(tFont), TRUE); // change font of button5
		}
		else if (winNum == id_interest_menu) {
			label2 = CreateWindow(TEXT("STATIC"), TEXT("Interests Menu"),
				WS_VISIBLE | WS_CHILD | SS_CENTER,
				165, 25, 160, 25,
				curr, (HMENU)4, NULL, NULL
			);
			SendMessage(label2, WM_SETFONT, WPARAM(hFont), TRUE); // change font of label2

			label3 = CreateWindow(TEXT("STATIC"), TEXT("[Enter Three Key Words]"),
				WS_VISIBLE | WS_CHILD | SS_CENTER,
				140, 60, 200, 25,
				curr, (HMENU)3, NULL, NULL
			);
			SendMessage(label3, WM_SETFONT, WPARAM(shFont), TRUE); // change font of label3

			label4 = CreateWindow(TEXT("STATIC"), TEXT("[Image Path]"),
				WS_VISIBLE | WS_CHILD | SS_CENTER,
				185, 120, 120, 25,
				curr, (HMENU)3, NULL, NULL
			);
			SendMessage(label4, WM_SETFONT, WPARAM(shFont), TRUE); // change font of label3

			textBox1 = CreateWindow(TEXT("EDIT"), TEXT("Or Enter image path: C:\\\\Users\\\\person\\\\test.txt"),
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				10, 150, 450, 25,
				curr, (HMENU)bgText_id, NULL, NULL
			);
			SendMessage(textBox1, WM_SETFONT, WPARAM(tFont), TRUE); // change font of textBox1

			textBox2 = CreateWindow(TEXT("EDIT"), TEXT("Enter Interests (interest1+interest2+interest3)"),
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				10, 90, 450, 25,
				curr, (HMENU)interest_id, NULL, NULL
			);
			SendMessage(textBox2, WM_SETFONT, WPARAM(tFont), TRUE); // change font of textBox2
			button6 = CreateWindow(TEXT("BUTTON"), TEXT("Submit"),
				WS_VISIBLE | WS_CHILD,
				10, 180, 200, 25,
				curr, (HMENU)enter_id, NULL, NULL
			);
			SendMessage(button6, WM_SETFONT, WPARAM(tFont), TRUE); // change font of textBox1
			button7 = CreateWindow(TEXT("BUTTON"), TEXT("Choose a random interest!"),
				WS_VISIBLE | WS_CHILD,
				10, 210, 200, 25,
				curr, (HMENU)interest_generator_id, NULL, NULL
			);
			SendMessage(button7, WM_SETFONT, WPARAM(tFont), TRUE); // change font of textBox1
			button8 = CreateWindow(TEXT("BUTTON"), TEXT("Back"),
				WS_VISIBLE | WS_CHILD,
				10, 250, 200, 25,
				curr, (HMENU)back_id, NULL, NULL
			);
			SendMessage(button8, WM_SETFONT, WPARAM(tFont), TRUE); // change font of textBox1

		}
		else if (winNum == id_setting_menu) {

			// labels in setting
			label4 = CreateWindow(TEXT("STATIC"), TEXT("Setting Menu"),
				WS_VISIBLE | WS_CHILD | SS_CENTER,
				160, 25, 135, 25,
				curr, (HMENU)4, NULL, NULL
			);
			//SetTextColor((HDC)label4, RGB(100, 22, 11));
			SendMessage(label4, WM_SETFONT, WPARAM(hFont), TRUE); // change font of label5
			label5 = CreateWindow(TEXT("STATIC"), TEXT("[Birthday]"),
				WS_VISIBLE | WS_CHILD | SS_CENTER,
				185, 60, 90, 25,
				curr, (HMENU)3, NULL, NULL
			);
			SendMessage(label5, WM_SETFONT, WPARAM(shFont), TRUE); // change font of label5
			label6 = CreateWindow(TEXT("STATIC"), TEXT("[Weather]"),
				WS_VISIBLE | WS_CHILD | SS_CENTER,
				185, 150, 90, 25,
				curr, (HMENU)3, NULL, NULL
			);
			SendMessage(label6, WM_SETFONT, WPARAM(shFont), TRUE); // change font of label6

			label7 = CreateWindow(TEXT("STATIC"), TEXT("[Holiday]"),
				WS_VISIBLE | WS_CHILD | SS_CENTER,
				195, 240, 75, 25,
				curr, (HMENU)3, NULL, NULL
			);
			SendMessage(label7, WM_SETFONT, WPARAM(shFont), TRUE); // change font of label7

			textBox3 = CreateWindow(TEXT("EDIT"), TEXT("Enter Birthday: DD MM"),
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				10, 90, 400, 25,
				curr, (HMENU)bd_id, NULL, NULL
			);
			SendMessage(textBox3, WM_SETFONT, WPARAM(tFont), TRUE); // change font of textBox3
			button9 = CreateWindow(TEXT("BUTTON"), TEXT("Update"),
				WS_VISIBLE | WS_CHILD,
				10, 120, 200, 25,
				curr, (HMENU)update_bd_id, NULL, NULL
			);
			SendMessage(button9, WM_SETFONT, WPARAM(tFont), TRUE); // change font of button9

			textBox4 = CreateWindow(TEXT("EDIT"), TEXT("Enter 1 to enable weather API (0 = disable)"),
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				10, 180, 400, 25,
				curr, (HMENU)weather_id, NULL, NULL
			);
			SendMessage(textBox4, WM_SETFONT, WPARAM(tFont), TRUE); // change font of textBox4

			button10 = CreateWindow(TEXT("BUTTON"), TEXT("Update"),
				WS_VISIBLE | WS_CHILD,
				10, 210, 200, 25,
				curr, (HMENU)update_weather_id, NULL, NULL
			);
			SendMessage(button10, WM_SETFONT, WPARAM(tFont), TRUE); // change font of button10
			textBox5 = CreateWindow(TEXT("EDIT"), TEXT("Enter holiday name and date: holiday DD MM"),
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				10, 270, 400, 25,
				curr, (HMENU)holiday_id, NULL, NULL
			);
			SendMessage(textBox5, WM_SETFONT, WPARAM(tFont), TRUE); // change font of textBox5
			button11 = CreateWindow(TEXT("BUTTON"), TEXT("Add"),
				WS_VISIBLE | WS_CHILD,
				10, 300, 200, 25,
				curr, (HMENU)update_holiday_id, NULL, NULL
			);
			SendMessage(button11, WM_SETFONT, WPARAM(tFont), TRUE); // change font of button11
			button12 = CreateWindow(TEXT("BUTTON"), TEXT("Back"),
				WS_VISIBLE | WS_CHILD,
				10, 340, 200, 25,
				curr, (HMENU)back_id, NULL, NULL
			);
			SendMessage(button12, WM_SETFONT, WPARAM(tFont), TRUE); // change font of button12

		}

		break;
	}
	// any time you interact with the app it comes here
	case WM_COMMAND: {
		//ShowWindow(GetConsoleWindow(), SW_HIDE);
		// checks ids to see what was interacted with 

		// save background to favourites folder
		if (LOWORD(wParam)== bgChanger_id) {
			
				//int len = GetWindowTextLength(textBox1) + 1;
				//wchar_t* title = new wchar_t;
				//GetWindowText(textBox1, title, len);
				//SetWindowText(hWnd, title);
				//check path first 
				PastImages temp;
				int success = temp.SaveImage();
				
				if (success == 1) {
					MessageBox(hWnd, _T("Background has been saved!"), _T("Success"), MB_ICONINFORMATION);
					winNum = 1;
				}
			
		}
		// find new background 
		else if (LOWORD(wParam)==skip_id) {
			BackgroundSetter newBG;
			int hasImage = newBG.checkPath();
			
			if (hasImage == 0) {
				// if no more backgrounds, the code copies favourites into the images folder
					// so old backgrounds will be seen
				BackgroundSetter newBG0;
				newBG0.loopFavouriteBG();
				MessageBox(hWnd, _T("Out of new backgrounds! :( \n Enter New Interests!"), _T("Error"), MB_ICONINFORMATION);
				//MessageBox(hWnd, _T("Enter interests to create backgrounds!"), _T("Error"), MB_ICONINFORMATION);
			}
			else {
				PastImages backgroundImage;
				int worked = skipBackground1();
				backgroundImage.DeleteImage();
				if (worked == 1) {
					MessageBox(hWnd, _T("Background has been changed!"), _T("Success"), MB_ICONINFORMATION);
					winNum = 1;
				}
				
			}
		}

		else if (LOWORD(wParam) == del_current_bg_id) {
			BackgroundSetter newBG;
			int hasImage = newBG.checkPath();
		
			PastImages backgroundImage;
			backgroundImage.DeleteImagePrevious();
				//int worked = skipBackground1();
		}
		else if (LOWORD(wParam) == enter_id) {
			int len2 = GetWindowTextLength(textBox2) + 1;
			wchar_t* interests = new wchar_t;
			GetWindowText(textBox2, interests, len2);
			string interests_string = wchar_to_string(interests);
			if (interests_string != "Enter Interests(interest1 + interest2 + interest3)") {
				BackgroundSetter newBg1;
				int check = newBg1.weatherCheck(interests_string);
				if (check !=  1) {
					retrieveImage(interests_string);
				}
				//retrieveImage(interests_string);
				SetWindowText(textBox2, L"Enter Interests(interest1 + interest2 + interest3)");
			}
			else {
				int len1 = GetWindowTextLength(textBox1) + 1;
				wchar_t* path = new wchar_t;
				GetWindowText(textBox1, path, len1);
				string filepath = wchar_to_string(path);
				reverseRetrieveImage(filepath);
				SetWindowText(textBox1, L"Or Enter image path: C:\\\\Users\\\\person\\\\test.txt");
			}
			

			
		}
		else if (LOWORD(wParam) == update_weather_id) {
			int len4 = GetWindowTextLength(textBox4) + 1;
			wchar_t* weather = new wchar_t;
			GetWindowText(textBox4, weather, len4);
			string w = wchar_to_string(weather);
			int weatherPref = stoi(w);
			UserInformation wp;
			wp.setWeatherPref(weatherPref);
			wp.storeWeatherPref();
			SetWindowText(textBox4, L"Enter 1 to enable weather API(0 = disable)");

			//SetWindowText(hWnd, weather);
		}
		else if (LOWORD(wParam) == update_bd_id) {
			int len3 = GetWindowTextLength(textBox3) + 1;
			wchar_t* bd = new wchar_t;
			GetWindowText(textBox3, bd, len3);
			string bd_string = wchar_to_string(bd);
			UserInformation b;
			b.splitBirthday(bd_string);
			b.storeBirthday();
			SetWindowText(textBox3, L"Enter birthday: dd mm");
		}
		else if (LOWORD(wParam) == update_holiday_id) {
			int len5 = GetWindowTextLength(textBox5) + 1;
			wchar_t* holiday = new wchar_t;
			GetWindowText(textBox5, holiday, len5);
			string holiday_string = wchar_to_string(holiday);
			UserInformation h;
			h.setHoliday(holiday_string);
			h.storeHoliday();
			SetWindowText(textBox5, L"Enter holiday: name dd mm");

		}
		else if (LOWORD(wParam) == interest_generator_id) {
			string newInterest = generateInterest();
			//CStringW inter = newInterest.c_str();
			//const wchar_t* new_inter = inter.GetString();
			retrieveImage(newInterest);
			string mes = "New Interest is "+ newInterest;
			CStringW inter = mes.c_str();
			const wchar_t* new_inter = inter.GetString();
			MessageBox(hWnd2, new_inter, _T("Interesting"), MB_ICONINFORMATION);
			//SetWindowText(hWnd, new_inter);

		}
		else if (LOWORD(wParam) == current_bg_id) {
			BackgroundSetter newBG1;
			newBG1.loopPreviousBG();
		}
		else if (LOWORD(wParam) == favourite_bg_id) {
			BackgroundSetter newBG1;
			newBG1.loopFavouriteBG();
		}
		// menu for main page
		// show interest page and hide main page
		else if (LOWORD(wParam) == id_interest_menu) {
			//MessageBeep(MB_OK);
			winNum = id_interest_menu;
			ShowWindow(hWnd2,
				SW_SHOW);
			UpdateWindow(hWnd2);
			ShowWindow(hWnd,
				SW_HIDE);
			UpdateWindow(hWnd);

		}
		//menu for main page
		// show settings page and hide main page 
		else if (LOWORD(wParam) == id_setting_menu) {
			//MessageBeep(MB_OK);
			winNum = id_setting_menu;
			ShowWindow(hWnd3,
				SW_SHOW);
			UpdateWindow(hWnd3);
			ShowWindow(hWnd,
				SW_HIDE);
			UpdateWindow(hWnd);

		}
		// leave (part of menu)
		else if (LOWORD(wParam) == id_exit_menu) {
			DestroyWindow(hWnd);
		}
		// return to main page based on where we are 
		else if (LOWORD(wParam) == back_id) {
			if (winNum == id_interest_menu) {
				ShowWindow(hWnd2,
					SW_HIDE);
				UpdateWindow(hWnd2);
				ShowWindow(hWnd,
					SW_SHOW);
				UpdateWindow(hWnd);
				
			}
			else if (winNum == id_setting_menu) {
				ShowWindow(hWnd3,
					SW_HIDE);
				UpdateWindow(hWnd3);
				ShowWindow(hWnd,
					SW_SHOW);
				UpdateWindow(hWnd);
				
			}
		}
		break;
	}
	case WM_PAINT:
		// determine title + background color
		hdc = BeginPaint(curr, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		// Here your application is laid out.
		// For this introduction, we just print out "Hello, Windows desktop!"
		// in the top left corner.
		TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));

		// Change color of labels
	case WM_CTLCOLORSTATIC:
	{
		// Change the title color of each page
		if (GetDlgCtrlID((HWND)lParam) == 4) // Target the specific component
		{
			HDC hdcStatic = (HDC)wParam; // or obtain the static handle in some other way
			SetTextColor(hdcStatic, RGB(220, 20, 60)); // text color
			SetBkColor(hdcStatic, RGB(255, 255, 255)); // backgound color
			return (LRESULT)GetStockObject(NULL_BRUSH);
		}
		// change the subtitle color
		if (GetDlgCtrlID((HWND)lParam) == 3) // Target the specific component
		{
			HDC hdcStatic = (HDC)wParam; // or obtain the static handle in some other way
			SetTextColor(hdcStatic, RGB(240, 128, 128)); // text color
			SetBkColor(hdcStatic, RGB(255, 255, 255)); // backgound color
			return (LRESULT)GetStockObject(NULL_BRUSH);
		}
	}

	// change color of textBox
	case WM_CTLCOLOREDIT:
	{

		HDC hdcStatic = (HDC)wParam; // or obtain the static handle in some other way
		SetTextColor(hdcStatic, RGB(0, 0, 0)); // text color
		SetBkColor(hdcStatic, RGB(255, 240, 245)); // backgound color
		return (LRESULT)GetStockObject(NULL_BRUSH);
	}

	

	// End application-specific layout section.
	EndPaint(curr, &ps);
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(curr, message, wParam, lParam);
		break;
	}



	return 0;
}

/*
int changeBackground(const wchar_t* imagePath) {
	//change background using windows api
	int success = SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (void*)imagePath, SPIF_UPDATEINIFILE);
	return success;
}
*/

//menu fucntion to create menu for main page 
void addMenus() {
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	AppendMenu(hFileMenu, MF_STRING, id_setting_menu, L"Settings");
	AppendMenu(hFileMenu, MF_STRING, id_interest_menu, L"Interests");
	AppendMenu(hFileMenu, MF_STRING, id_exit_menu, L"Exit");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"Menu");
	SetMenu(hWnd, hMenu);
	
}

string wchar_to_string(wchar_t* str)
{
	string converted="";
	while (*str)
		converted += (char)*str++;
	return  converted;
}

string generateInterest() {
	srand(time(NULL));
	vector<string> column1;
	ifstream InterestFile("..\\BG_Manager\\random_interests.txt");
	//check if it failed
	string c1;
	if (!(InterestFile.fail())) {
		//read the file line by line
		//each time split in 3 based on columns
		while (InterestFile >> c1) {
			//push to the vectors
			column1.push_back(c1);
		}
		InterestFile.close();

		int rand1 = rand() % column1.size();
		return column1[rand1];
	}

}

void retrieveImage(string searchTerms) {

	// Assumes the code is excecuted from the same folder as where the python script is stored
	// If it does not, you can provide it the absolute location of the RetrieveImage.py script
	
	string command = "echo Loading Backgrounds for "+searchTerms+" && python3 RetrieveImage.py " + searchTerms;
	system(command.c_str());
}



void reverseRetrieveImage(string filepath) {

	// Assumes the code is excecuted from the same folder as where the python script is stored
	// If it does not, you can provide it the absolute location of the RetrieveImage.py script
	string command = "echo Loading Backgrounds && python3 ReverseRetrieveImage.py " + filepath;
	system(command.c_str());
}