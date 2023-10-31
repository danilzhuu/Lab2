#pragma once
#include <Windows.h>
//����������� ������������� ����� windowsx.h ���������� ��� 
//����������� ��������� ��������������� ��������� ��� ������ � ��������.
#include <windowsx.h>

#include "CHLimiter.h"
//������� � ����� ������ �������� � ��������� �� ������ �������
//� ����� �������� �������
class CBall
{
	HBRUSH hBrush;//hBrush � ������� ����� ��� ��������� ������. 
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
