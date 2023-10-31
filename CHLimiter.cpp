#include "CHLimiter.h"
CHLimiter::CHLimiter(int xmin, int xmax, int y)
{
	this->xmax = xmax;
	this->xmin = xmin;
	this->color_g = 0;
	this->color_r = 0;
	this->y = y;
}
CHLimiter::~CHLimiter() {

}
void CHLimiter::Draw(HDC dc)
//Метод MoveToEx перемещает позицию рисования, 
//а метод LineTo – отрисовывает линию с текущей позиции до указанной.
{
	HGDIOBJ original = SelectObject(dc, GetStockObject(DC_PEN));
	SetDCPenColor(dc, RGB(this->color_r, this->color_g, 0));
	::MoveToEx(dc, this->xmin, this->y, NULL);
	::LineTo(dc, this->xmax, this->y);
	SelectObject(dc, original);
}

int CHLimiter::GetMaxX()
{
	return this->xmax;
}

int CHLimiter::GetMinX()
{
	return this->xmin;
}

int CHLimiter::GetY()
{
	return this->y;
}
// методы MoveX и MoveY для препятствия
//Параметр inc показывает величину изменения положения
void CHLimiter::MoveX(int inc) {
	this->xmin += inc;
	this->xmax += inc;
}

void CHLimiter::MoveY(int inc) {
	this->y += inc;
}

void CHLimiter::SetColorRed() {
	this->color_r = 255;
	this->color_g = 0;
}

void CHLimiter::SetColorGreen() {
	this->color_r = 0;
	this->color_g = 255;
}

void CHLimiter::SetColorBlack() {
	this->color_r = 0;
	this->color_g = 0;
}