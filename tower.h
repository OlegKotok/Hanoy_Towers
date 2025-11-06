#ifndef TOWERS
 #define TOWERS
 #include <windows.h>
 #include <windowsx.h>
 typedef unsigned small;
 //описание класса Tower

 namespace hanoy
 {
  class tower
  {
    private:  
	  small a[100]; //шпиндель с низу в верх
	  small *b;		//самый верхний елемент шпинделя
	  small c;		//счетчик елементов
	public:
	  tower();
	  tower(small n); //конструктор
	  bool put(small g); //добавить елемент g.
	  small get(); //забрать верхний елемент

	  bool is_full(small height) const; //вернуть количество елементов
	  bool can_add(small d) const; //возможность добавить елемент

	  void Show( HDC &dc, /*на чем рисуем*/
				 unsigned position,
				 HPEN &borderPen, /*обводка*/
				 HBRUSH &borderBrush, /*заливка*/
				 HPEN &towerPen, /*цвет башен*/
				 HBRUSH &ringBrush0, HBRUSH &ringBrush1, /*обводка и заливка колец*/
				 HFONT& Font /*шрифт*/
			    );

    friend bool operator<<(tower &a, tower &b);
	friend bool operator>>(tower &b, tower &a);
	//friend void PrintTowewrs(tower &A, tower &B, tower &C); //вывод башен
  };
 };
#endif