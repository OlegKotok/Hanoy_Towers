//скелет игры
#include <windows.h>
#include <windowsx.h>
#include <sstream>
//#include "colors.h"
#include "game.h"
#include "localization.h"
#include <string.h>

unsigned N=10, M=3; //количество колец и башен
const char className[]="gameForm"; //имя класса окна
HWND main_window; //дескриптор главного окна

game::field *gamefield; //!обьявляем класс игры

//прототипы функций
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM); //оконная функция для обработки событий окна
BOOL OnCreate(HWND, void*);
void OnPaint(HWND);
void OnDestroy(HWND);
void OnClick(HWND, BOOL, int, int, UINT);
void OnMouseMove(HWND, int, int, UINT);
RECT arrowArea; //зона рисования стрелки
void ShowGameInfo();


int WINAPI WinMain(HINSTANCE hThisInstance /* дескриптор приложения */,
                   HINSTANCE, LPSTR cmdLine, int showStyle /* режим показа окна */)

{
	//определяем параметры игры
	std::stringstream s;
	s<<cmdLine;
	s>>M>>N;
	if (M<3) M=3;
	if (M>5) M=5;

	if (N<M) N=M; //ограничение минимума колец
	if (N>M*5) N=M*5;

	gamefield=new game::field(M, N); //!создаем класс игры

	//создадим класс окна
    WNDCLASSEX wc; //дескриптор класса окна
    ZeroMemory(&wc, sizeof(wc));
    wc.hInstance=hThisInstance; //дескриптор приложения
    wc.lpszClassName=className; //имя класса
    wc.lpfnWndProc=WinProc; //функция обработки событий
    wc.cbSize = sizeof(WNDCLASSEX);

    wc.style=CS_VREDRAW|CS_VREDRAW; //разрешаем автоматическую перерисовку
    wc.hIcon=LoadIcon(NULL, IDI_APPLICATION); //устанавливаем иконку Windows
    wc.hCursor=LoadCursor(NULL, IDC_ARROW); //устанавливаем курсор Windows
    wc.lpszMenuName = NULL; /* No menu */
    wc.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH); //белый фон

    RegisterClassEx(&wc); //регестрируем класс окна

    //Создаем окно
    main_window=CreateWindow( className, "Hanoi Towers", /*имя класса и заголовок */
							  WS_OVERLAPPEDWINDOW, 35, 40, gamefield->GetWindowWidth()+10, gamefield->GetWindowHeight()+27, /* стиль окна, позиция и размеры */
                              HWND_DESKTOP, NULL /* No menu */, hThisInstance /*дескриптор приложения*/, NULL /*доп.данные*/
                             );

    ShowWindow(main_window, showStyle); //отображаем окно


    //обработка сообщений
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0))
    {
           TranslateMessage(&msg); //Translate virtual-key messages into character messages
           DispatchMessage(&msg);  //Send message to WindowProcedure
    }

    return msg.wParam;
}


////////////////////////////////////////////////////////////////////////////////

/* This function is called by the Windows function DispatchMessage( ) */
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
         HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
		 HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
		 HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
		 HANDLE_MSG(hwnd, WM_LBUTTONDOWN, OnClick);
		 HANDLE_MSG(hwnd, WM_MOUSEMOVE, OnMouseMove);
         default: return DefWindowProc(hwnd, msg, wParam, lParam); //обработка поумолчанию
    }
    return 0;
}

//функции-обработчики
BOOL OnCreate(HWND hwnd, void*)
{
    gamefield->Start();
	arrowArea.left=0; arrowArea.right=gamefield->GetWindowWidth();
	arrowArea.top=0; arrowArea.bottom=80-1;
	return true;
}

void OnPaint(HWND hwnd)
{
    PAINTSTRUCT paintstruct;
    HDC hdc=BeginPaint(hwnd, &paintstruct);
	gamefield->Show(hdc, paintstruct.rcPaint);//рисуем
    EndPaint(hwnd, &paintstruct);
	static bool firstshow=true;
	if (firstshow){
		firstshow=false;
		ShowGameInfo();
	};
}

void OnDestroy(HWND hwnd)
{
    delete gamefield; //удаляем игру
	PostQuitMessage(0);
}

void ShowGameInfo()
{
	char msg[200];
	std::string format = g_localizer.GetA("game_info");
	sprintf(msg, format.c_str(), N);



	MessageBox(main_window, msg, g_localizer.GetA("window_title").c_str(), MB_OK|MB_ICONINFORMATION);
}

//////////////////////////////////////////////////////////////////////////


static bool fSelectFirstTower=false;  //выделена первая башня для перемещения

void OnClick(HWND hwnd, BOOL fdbclick, int x, int y, UINT keyFlugs)
{
	static unsigned fromTower, toTower;
	unsigned position=gamefield->GetTowersIndex(x, y); //получаем номер башни
	RECT towerRect;

	if (position){
		if (!fSelectFirstTower) {

			fromTower=position;
			fSelectFirstTower=true;
			gamefield->setSelectTower(position); //выделенная башня
			//определяем зону перерисовки
			towerRect.left=40 + (5*40+30)*(position-1);
			towerRect.right=towerRect.left+200;
			towerRect.top=80; towerRect.bottom=80+40*7+2;
			RedrawWindow(main_window, &towerRect, NULL, RDW_NOERASE|RDW_NOFRAME|RDW_INVALIDATE); //зарисовываем исходную башню
		}
		else if (position!=fromTower){
			//перемещение разрешено
			toTower=position;
			if (gamefield->Move(fromTower-1, toTower-1)) {
				//перемещение
				fSelectFirstTower=false;
				gamefield->setSelectTower(0); //снять выделение
				gamefield->setTargetTower(0);

				//тест на выиграш
				if (gamefield->is_win()) {
					char msg[200];
					std::string format = g_localizer.GetA("win_message");
					sprintf(msg, format.c_str(), gamefield->getTurnNumber());




					MessageBox(main_window, msg, g_localizer.GetA("win_title").c_str(), MB_OK|MB_ICONINFORMATION);
				};
			}
			else {
				fSelectFirstTower=true;
				gamefield->setSelectTower(position); //новое выделение
				fromTower=position; //!новая исходная позиция
			}
			RedrawWindow(main_window, NULL, NULL, RDW_NOFRAME|RDW_ERASE|RDW_INVALIDATE|RDW_ERASENOW|RDW_UPDATENOW|RDW_INTERNALPAINT); //полное обновление окна
		};
	};
};

void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlugs)
{
	static unsigned firstSelect, predSelect=0;
	if (fSelectFirstTower) {
		firstSelect=gamefield->GetTowersIndex(x, y); //на какую башню наведена мыша
		if (firstSelect!=predSelect){
			gamefield->setTargetTower(firstSelect);
			RedrawWindow(main_window, &arrowArea, NULL, RDW_NOFRAME|RDW_ERASE|RDW_INVALIDATE|RDW_ERASENOW|RDW_UPDATENOW); //принудительный показ
		};
		predSelect=firstSelect;
	};
};
