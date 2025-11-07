#ifndef MY_COLORS
 #define MY_COLORS
 
 namespace colors{
		  //const COLORREF border0=RGB(255, 255, 192);
		  //const COLORREF border1=RGB(184,255,164); //цвет заливки
	      const COLORREF tower0=RGB(168, 82, 32);
		  const COLORREF tower1=RGB(0, 128, 0); //цвет башен
		  const COLORREF ring0=RGB(0, 0, 255);
		  const COLORREF ring1=RGB(255, 128, 64); //цвет колец
		  const COLORREF selectColor1=RGB(235, 255, 245);
		  const COLORREF selectColor2=RGB(255, 255, 224); //цвет колец

		  HPEN borderPen, towerPen0, towerPen1, linePen; //карандаши
		  HBRUSH borderBrush, ringBrush0, ringBrush1, selectBrush; //зарисовка

 }; //цвета игровых обьектов

#endif