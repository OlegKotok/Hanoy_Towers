#include "game.h"
#include <cstdlib>
#include <ctime>
#include <ctype.h>
#include <conio.h>
#include "colors.h"

 namespace game
 {
	 field::field(unsigned m, unsigned n):ctowers(m), crings(n), selectTower(0), targetTower(0)
	 {
		 //определяем размеры окна
		 window_width=40 + 40*5*ctowers + (ctowers-1)*30 + 40;
		 window_height=80+40*7+65;
		 //выделяем память под указатели на башни
		 towers = new hanoy::tower[m];

		 //создаем кисти
		 colors::towerPen0=CreatePen(PS_SOLID, 4, colors::tower0); //коричневый
		 colors::towerPen1=CreatePen(PS_SOLID, 4, colors::tower1); //зеленый
		 colors::linePen=CreatePen(PS_SOLID, 2, RGB(64, 0, 128)); //темно-синий
		 
		 colors::borderPen=CreatePen(PS_SOLID, 1, RGB(192, 192, 192)); //обводка
		 colors::borderBrush=GetStockBrush(NULL_BRUSH); //заливка
		 colors::selectBrush=CreateSolidBrush(colors::selectColor1);
		 
		 colors::ringBrush0=CreateSolidBrush(colors::ring0); //синий
		 colors::ringBrush1=CreateSolidBrush(colors::ring1); //красный

		 //создаем шрифт
		 LOGFONT font_type;
		 ZeroMemory(&font_type, sizeof(font_type)); //обнуляем
		 font_type.lfHeight=18;
		 font_type.lfWeight=FW_BOLD;
		 strcpy(font_type.lfFaceName, "Tahoma"); //Tahoma, Georgia, Times New Roman  
		 hFont=CreateFontIndirect(&font_type);
	 };
	 
	 field::~field()
	 {
		 delete[] towers;
	 };

	 void field::Start()
	 {
		 nhod=0;
		 
		 //разбрасываем кольца
		 unsigned position; //номер башни
		 srand(unsigned(time(NULL)));
		 for(unsigned j=crings; j>0; j--) //кольца с самого большого до самого малого
		 {
			 position=rand()%ctowers; //выбор штыря
			 towers[position].put(j);
		 };
	};

	unsigned field::GetTowersIndex(int x, int y) const
	{
		if (y>=80 && y<=80+40*7) {
			for(unsigned j=0; j<ctowers; j++){
				//проверяем входят ли координаты в эту башню
				unsigned X=40+(5*40+30)*j; //начало зоны башни
				if (x>=X && x<=X+5*40) return j+1;
			};
		};
		return 0; //ничего не нашли
	};

	bool field::Move(unsigned p1, unsigned p2)
	{
		if (towers[p1] >> towers[p2]) {
			nhod++;
			return true;
		}
		else return false;
	};

    void field::Show(HDC &hdc/*дескриптор холста*/, RECT& drawRect/*зона обновления*/) 
	{
		RECT my_zone;
		my_zone.left=40; my_zone.right=GetWindowWidth();
		my_zone.top=80; my_zone.bottom=80+7*40+40;
		if (isInRefreshZone(my_zone /*что*/, drawRect /*зона*/)) {
			//рисуем башни
			unsigned x0, y0=80;
			for(unsigned j=0; j<ctowers; j++) {
				//определяем подзону башни
				x0=40+(5*40+30)*j;
				my_zone.left=x0; my_zone.right=x0+40*5;
				my_zone.top=y0; my_zone.bottom=y0+40*7+40;

				if (isInRefreshZone(my_zone /*что*/, drawRect /*зона*/)){
					towers[j].Show(
									hdc /*то, на чем рисуем*/, j /*номер башни*/,
									colors::borderPen, /*обводка*/
									(j+1==selectTower)?colors::selectBrush : colors::borderBrush,
									(j%2)?colors::towerPen1 : colors::towerPen0, /*башня*/
									colors::ringBrush0, colors::ringBrush1, /*кольца*/
									hFont
								  );
				};//if
			};
		};

		//рисуем стрелку
		if (selectTower && targetTower) {
			SelectPen(hdc, colors::linePen);
			//определяем координаты
			const unsigned xfrom=140+230*(selectTower-1);
			const unsigned xto=140+230*(targetTower-1);
			const unsigned y0=80;
			//рисуем линию
			MoveToEx(hdc, xfrom, y0-1, NULL);
			LineTo(hdc, xfrom, y0-50);
			LineTo(hdc, xto, y0-50);
			LineTo(hdc, xto, y0-1);
			//рисуем стрелку
			LineTo(hdc, xto+10, y0-18);
			LineTo(hdc, xto, y0-1);
			LineTo(hdc, xto-10, y0-18);
		};

	};

	bool field::isInRefreshZone(RECT &targetArea /*что*/, RECT &refreshArea /*зона*/) const //тест на необходимость прорисовки
	{
		return (refreshArea.left<=targetArea.right && refreshArea.right>=targetArea.left   &&   refreshArea.top<=targetArea.bottom && refreshArea.bottom>=targetArea.top);
	};

 };