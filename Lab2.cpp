// Lab2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab2.h"
#include "CBall.h"
#include "CHLimiter.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE g_instance;                                // текущий экземпляр
HWND g_window;
//Для добавления границы в программу вносим доработки в основной код программы
CBall ball(100, 100, 200, 90, 50);
CHLimiter lim(250, 350, 300);

WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

void OnIdle() {
    DWORD ticks = GetTickCount();

    ball.Move(ticks);
    InvalidateRect(g_window, NULL, TRUE);//InvalidateRect говорит системе, 
    //что указанное окно содержит неверную графическую информацию, 
    //в ответ на этот вызов система посылает приложению WM_PAINT.
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }

    RECT cr;//будет описывать прямоугольник границ окна
    GetClientRect(g_window, &cr);
    ball.SetBounds(cr);
    ball.SetHLimiter(&lim);

    MSG msg;

    // Цикл основного сообщения:
    while (1) {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                break;
            }
            DispatchMessage(&msg);
        }
        else {
            Sleep(20);//добавила паузу перед обновлением экрана размером в 20 мс. 
            //чтобы шарик меньше мерцал
            OnIdle();
        }
    }

    return (int)msg.wParam;
}



// Регистрирует класс окна.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB2);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//   Сохраняет маркер экземпляра и создает главное окно
//   В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//   создается и выводится главное окно программы.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    g_instance = hInstance; // Сохранить маркер экземпляра в глобальной переменной
    g_window = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!g_window)
    {
        return FALSE;
    }

    ShowWindow(g_window, nCmdShow);
    UpdateWindow(g_window);

    return TRUE;
}

// Обрабатывает сообщения в главном окне.
//
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        //реализации движения.
    case WM_KEYDOWN:
        switch (wParam) {
        case VK_DOWN:
            lim.MoveY(3);
            break;
        case VK_UP:
            lim.MoveY(-3);
            break;
        case VK_LEFT:
            lim.MoveX(-3);
            break;
        case VK_RIGHT:
            lim.MoveX(3);
            break;
        case 0x42: // Кнопка B:
            lim.SetColorBlack();
            break;
        case 0x47: // Кнопка G:
            lim.SetColorGreen();
            break;
        case 0x52: // Кнопка R:
            lim.SetColorRed();
            break;
        }
        break;
    case WM_SIZE:
    {
        RECT cr;
        GetClientRect(g_window, &cr);
        ball.SetBounds(cr);
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        ball.Draw(hdc);
        lim.Draw(hdc);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

