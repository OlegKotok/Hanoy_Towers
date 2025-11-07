//модуль игры
#ifndef MAIN_UNIT
 #define MAIN_UNIT

 #include "tower.h"
 #include <windows.h>
 #include <windowsx.h>

 namespace game
 {
	class field //класс игровое поле
	{
	   private:
		  unsigned ctowers, crings; //колец и башен
		  unsigned nhod; //номер хода
		  hanoy::tower* towers; //массив башен
		  unsigned window_width, window_height;
		  unsigned selectTower; //индекс выделенной башни
		  unsigned targetTower; //индекс башни назначения (OnMouseMove)
		  bool isInRefreshZone(RECT &targetArea /*что*/, RECT &refreshArea /*зона*/) const;
		  HFONT hFont;
       public:
		  field(unsigned /*башен*/, unsigned/*колец*/);
		  void Start(); //запуск игры
		  void Show(HDC &hdc/*дескриптор холста*/, RECT& drawRect/*зона обновления*/); //отоюражение колец

		  unsigned GetTowersIndex(int x, int y) const; //вернуть номер башни
		  bool Move(unsigned p1, unsigned p2); //переместить кольца
		  inline void setSelectTower(unsigned c) {selectTower=c;};
		  inline void setTargetTower(unsigned c) {targetTower=c;};
		  
		  inline unsigned GetWindowWidth() const {return window_width;};
		  inline unsigned GetWindowHeight() const {return window_height;};
		  inline bool is_win() const {return towers[ctowers-1].is_full(crings);};
		  inline unsigned getTurnNumber() const {return nhod;};
		  ~field();		 
	};
 }

#endif