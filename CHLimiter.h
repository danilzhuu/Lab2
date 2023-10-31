#pragma once
#include <Windows.h>
#include <windowsx.h>
class CHLimiter
{
	//����������� ��������������� ���������� y � ������ ������������ 
	//� ����������� xmin, xmax � ������ � ��������� �� �����������. 
	// MoveX � MoveY ��� �����������
	int y;
	int xmin, xmax;
	int color_r;
	int color_g;
public:
	CHLimiter(int xmin, int xmax, int y);
	~CHLimiter();
	void Draw(HDC ds);
	int GetMaxX();
	int GetMinX();
	int GetY();

	void MoveX(int inc);
	void MoveY(int inc);

	void SetColorRed();
	void SetColorGreen();
	void SetColorBlack();
};