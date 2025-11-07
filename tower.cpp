//реализация класса
#include "tower.h"

namespace hanoy
{
	tower::tower()
	{
		*a=0; //самый нижний
		c=0; //количество добавленых елементов
		b=a; //верхний елемент
	};
	
	tower::tower(small n)
	{
		*a=0; //самый нижний
		for(small j=n; j>0; j--) a[n+1-j]=j;
		c=n; //количество добавленых елементов
		b=a+n;//верхний елемент
	};

	bool tower::can_add(small d) const
	{
		if (d && ((d<*b)||(*b==0))) return true;
		return false;
	}

	bool tower::is_full(small height) const
	{
		//определить высоту башни
		return (height==c);
	};


	bool tower::put(small g)
	{
		if (g && ((g<*b)||(*b==0))) //ноль не ставить. ставить только болеше нижнего
		{
			*++b=g; //добавить елемент g
			c++;
			return true;
		}
		else return false;
	}

	small tower::get(){
		if (c>0){
			c--;
			return *b--;
		}
		else return 0; //нет обьектов
	};

////////////////////Операторные функции//////////////////////

	bool operator<<(tower &a, tower &b)
	{
		small tmp=b.get();
		if (a.can_add(tmp)){
			a.put(tmp); 
			return true;  //передвинули успешно
		}
		else {
			b.put(tmp); //вставляем назад
			return false;
		}
	};

	bool operator>>(tower &b, tower &a)
	{
		small tmp=b.get();
		if (a.can_add(tmp)){
			a.put(tmp);
			return true; //передвинули успешно
		}
		else {
			b.put(tmp); //вставляем назад
			return false;
		}
	};

	void tower::Show( HDC &dc, /*на чем рисуем*/
					  unsigned position,
					  HPEN &borderPen, /*обводка*/
				      HBRUSH &borderBrush, /*заливка*/
					  HPEN &towerPen, /*цвет башен*/
				      HBRUSH &ringBrush0, HBRUSH &ringBrush1, /*обводка и заливка колец*/
					  HFONT& Font
					)
	{
		const unsigned x0=40+(5*40+30)*position/*от нуля*/;
		const unsigned y0=80;
		//рисуем обводку
		SelectPen(dc, borderPen);
        SelectBrush(dc, borderBrush);
        Rectangle(dc, x0, y0, x0+40*5, y0+40*7+1);
		//рисуем стержень
		SelectPen(dc, towerPen);
		MoveToEx(dc, x0+1, y0+7*40-1, NULL);
		LineTo(dc, x0+5*40-1, y0+7*40-1);
		MoveToEx(dc, x0+100, y0+40, NULL);
		LineTo(dc, x0+100, y0+7*40-1);
		//рисуем кольца
		SelectPen(dc, GetStockPen(BLACK_PEN)); //карандаш
		unsigned x1, y, x2;
		if (c) for (unsigned i=1; i<=c; i++) {
			SelectBrush(dc, ((a[i]%2)?ringBrush1:ringBrush0)); //определяем цвет
			y=y0+7*40 - (i*13) - 3;
			x1=x0+100 - 5 - a[i]*6;
			x2=x0+100 + 5 + a[i]*6;
			Rectangle(dc, x1, y, x2, y+12);
		};
		//добавляем надпись
		RECT text_zone;
		char i='A'+position;
		text_zone.left=x0+80+1; text_zone.right=text_zone.left+40;
		text_zone.top=y0+40*7+6; text_zone.bottom=text_zone.top+32;
		SelectFont(dc, Font);
		DrawText(dc, &i, 1, &text_zone, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	};

}
