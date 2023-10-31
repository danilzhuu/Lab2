#include "CBall.h"

int sign(double x) {
	if (x >= 0) return 1;
	if (x < 0) return -1;
}

CBall::CBall(double x, double y, double vx, double vy, double r) {
	this->hBrush = CreateSolidBrush(RGB(12, 20, 140));
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;

	this->r = r;
	this->prevTicks = GetTickCount();
}

CBall::~CBall() {
	DeleteObject(this->hBrush);
}

void CBall::Draw(HDC dc) {
	HBRUSH hOldBrush = SelectBrush(dc, this->hBrush);
	Ellipse(dc, x - r, y - r, x + r, y + r);
	SelectBrush(dc, hOldBrush);
}

void CBall::ResolveCollisions() {
	bool hit_left = this->x - r <= 0;
	bool hit_right = this->x + r >= this->bounds.right;
	bool hit_top = this->y - r <= 0;
	bool hit_bottom = this->y + r >= this->bounds.bottom;

	if (hit_right && this->vx > 0 || hit_left && this->vx < 0) {
		this->vx = -this->vx;
	}

	if (hit_bottom && this->y > 0 || hit_top && this->vy < 0) {
		this->vy = -this->vy;
	}

	// Столкновение с CHLimiter

	if ((this->x + r >= limit1->GetMinX()) && (this->x - r) <= limit1->GetMaxX()) {
		if (this->vy > 0) {
			int lim_rel_y = limit1->GetY() - this->y;
			if ((lim_rel_y < this->r) && (lim_rel_y > 0)) {
				this->vy = -this->vy;
			}
		}
		else {
			int lim_rel_y = this->y - limit1->GetY();
			if ((lim_rel_y < this->r) && (lim_rel_y > 0)) {
				this->vy = -this->vy;
			}
		}
	}
}

void CBall::Move(DWORD ticks) {
	//расчет времени между движениями в секундах
	double s_delta = ((double)(ticks - this->prevTicks) / 1000.0);
	this->prevTicks = ticks;

	this->ResolveCollisions();

	this->x += this->vx * s_delta;
	this->y += this->vy * s_delta;
}

void CBall::SetBounds(RECT bnds) {
	this->bounds = bnds;
}

void CBall::SetHLimiter(CHLimiter* limiter) {
	this->limit1 = limiter;
}