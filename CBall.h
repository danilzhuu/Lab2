#pragma once
#include <Windows.h>
//Подключение заголовочного файла windowsx.h необходимо для 
//подключения некоторых вспомогательных библиотек для работы с графикой.
#include <windowsx.h>

#include "CHLimiter.h"
//Добавим в класс шарика параметр – указатель на объект границы
//и метод передачи границы
class CBall
{
	HBRUSH hBrush;//hBrush – рабочая кисть для отрисовки шарика. 
	DWORD prevTicks;
	double x, y;
	double vx, vy;
	double r;

	RECT bounds;
	CHLimiter* limit1;

	void ResolveCollisions();
public:
	CBall(double x, double y, double vx, double vy, double r);
	~CBall();
	void Draw(HDC dc);
	void Move(DWORD ticks);
	void SetBounds(RECT bnds);
	void SetHLimiter(CHLimiter* limiter);
};
