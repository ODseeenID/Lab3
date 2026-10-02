#include <windows.h>
#include "resource.h" // підключення файлу ресурсів 

// =======================================================================
// Клас для малювання Яблуні 
// =======================================================================
class AppleTree {
public:
    void show(HDC dc, int X, int Y) {
        HBRUSH brush;
        HGDIOBJ oldBrush;

        // Стовбур
        brush = CreateSolidBrush(RGB(139, 69, 19));
        oldBrush = SelectObject(dc, brush);
        Rectangle(dc, X, Y, X + 20, Y + 80);
        SelectObject(dc, oldBrush);
        DeleteObject(brush);

        // Крона
        brush = CreateSolidBrush(RGB(34, 139, 34));
        oldBrush = SelectObject(dc, brush);
        Ellipse(dc, X - 40, Y - 50, X + 60, Y + 30);
        SelectObject(dc, oldBrush);
        DeleteObject(brush);

        // Яблука
        brush = CreateSolidBrush(RGB(255, 0, 0));
        oldBrush = SelectObject(dc, brush);
        Ellipse(dc, X - 20, Y - 30, X - 5, Y - 15);
        Ellipse(dc, X + 10, Y - 40, X + 25, Y - 25);
        Ellipse(dc, X + 30, Y - 10, X + 45, Y + 5);
        Ellipse(dc, X - 10, Y, X + 5, Y + 15);
        SelectObject(dc, oldBrush);
        DeleteObject(brush);
    }
};

// =======================================================================
// Клас для малювання Будинку
// =======================================================================
class House {
public:
    void show(HDC dc, int X, int Y) {
        HBRUSH brush;
        HGDIOBJ oldBrush;

        // Фасад
        brush = CreateSolidBrush(RGB(254, 255, 220));
        oldBrush = SelectObject(dc, brush);
        Rectangle(dc, X, Y, X + 160, Y + 120);
        SelectObject(dc, oldBrush);
        DeleteObject(brush);

        // Дах
        POINT roof[3] = { {X - 20, Y}, {X + 80, Y - 70}, {X + 180, Y} };
        brush = CreateSolidBrush(RGB(178, 34, 34));
        oldBrush = SelectObject(dc, brush);
        Polygon(dc, roof, 3);
        SelectObject(dc, oldBrush);
        DeleteObject(brush);

        // Двері
        brush = CreateSolidBrush(RGB(139, 69, 19));
        oldBrush = SelectObject(dc, brush);
        Rectangle(dc, X + 20, Y + 40, X + 60, Y + 120);
        SelectObject(dc, oldBrush);
        DeleteObject(brush);

        // Вікно
        brush = CreateSolidBrush(RGB(135, 206, 235));
        oldBrush = SelectObject(dc, brush);
        Rectangle(dc, X + 90, Y + 30, X + 140, Y + 80);
        // Рама
        MoveToEx(dc, X + 115, Y + 30, nullptr);
        LineTo(dc, X + 115, Y + 80);
        MoveToEx(dc, X + 90, Y + 55, nullptr);
        LineTo(dc, X + 140, Y + 55);

        SelectObject(dc, oldBrush);
        DeleteObject(brush);
    }
};

// =======================================================================
// Клас для малювання Хмари 
// =======================================================================
class Cloud {
public:
    void show(HDC dc, int X, int Y) {
        HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
        HGDIOBJ oldBrush = SelectObject(dc, brush);
        HPEN pen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
        HGDIOBJ oldPen = SelectObject(dc, pen);

        Ellipse(dc, X, Y, X + 60, Y + 40);
        Ellipse(dc, X + 30, Y - 20, X + 100, Y + 50);
        Ellipse(dc, X + 70, Y + 10, X + 130, Y + 40);

        SelectObject(dc, oldPen);
        SelectObject(dc, oldBrush);
        DeleteObject(pen);
        DeleteObject(brush);
    }
};

// =======================================================================
// Клас для малювання Квітки 
// =======================================================================
class Flower {
public:
    void show(HDC dc, int X, int Y) {
        // Стебло
        HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 128, 0));
        HGDIOBJ oldPen = SelectObject(dc, pen);
        MoveToEx(dc, X, Y, nullptr);
        LineTo(dc, X, Y + 30);
        SelectObject(dc, oldPen);
        DeleteObject(pen);

        // Пелюстки
        HBRUSH brush = CreateSolidBrush(RGB(255, 105, 180));
        HGDIOBJ oldBrush = SelectObject(dc, brush);
        Ellipse(dc, X - 15, Y - 10, X + 5, Y + 10);
        Ellipse(dc, X - 5, Y - 10, X + 15, Y + 10);
        Ellipse(dc, X - 10, Y - 15, X + 10, Y + 5);
        Ellipse(dc, X - 10, Y - 5, X + 10, Y + 15);
        SelectObject(dc, oldBrush);
        DeleteObject(brush);

        // Центр
        brush = CreateSolidBrush(RGB(255, 255, 0));
        oldBrush = SelectObject(dc, brush);
        Ellipse(dc, X - 5, Y - 5, X + 5, Y + 5);
        SelectObject(dc, oldBrush);
        DeleteObject(brush);
    }
};

// =======================================================================
// Малювання всієї сцени
// +параметри skyColor та hideClouds
// =======================================================================
void DrawScene(HDC dc, int width, int height, COLORREF skyColor, bool hideClouds) {
    HBRUSH brush;
    HGDIOBJ oldBrush;

    // НЕБО, де замість RGB тепер змінна skyColor
    brush = CreateSolidBrush(skyColor);
    oldBrush = SelectObject(dc, brush);
    Rectangle(dc, 0, 0, width, height / 2);
    SelectObject(dc, oldBrush);
    DeleteObject(brush);

    // ЗЕМЛЯ (Трава)
    brush = CreateSolidBrush(RGB(124, 252, 0));
    oldBrush = SelectObject(dc, brush);
    Rectangle(dc, 0, height / 2, width, height);
    SelectObject(dc, oldBrush);
    DeleteObject(brush);

    // Хмари, що малюються якщо hideClouds == false
    if (!hideClouds) {
        Cloud cloud;
        cloud.show(dc, 100, 50);
        cloud.show(dc, 400, 80);
        cloud.show(dc, 650, 30);
    }

    // Будинок
    House house;
    house.show(dc, 400, height / 2 - 80);

    // Яблуні
    AppleTree tree;
    tree.show(dc, 100, height / 2 - 20);
    tree.show(dc, 730, height / 2 + 20);
    tree.show(dc, 250, height / 2 + 50);

    // Квіти
    Flower flower;
    flower.show(dc, 350, height / 2 + 130);
    flower.show(dc, 525, height / 2 + 190);
    flower.show(dc, 660, height / 2 + 130);
    flower.show(dc, 850, height / 2 + 190);
    flower.show(dc, 150, height / 2 + 190);
}

// =======================================================================
// Віконна процедура
// =======================================================================
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    //+статичні змінні для збереження стану (малювати, колір, приховання)
    static bool showImage = false;
    static COLORREF skyColor = RGB(135, 206, 250);
    static bool hideClouds = false;

    switch (message) {
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        switch (wmId) {
        case ID_40001: // "Draw"
            showImage = true;
            InvalidateRect(hwnd, nullptr, TRUE);
            break;

        case ID_40002: // "Change color"
            skyColor = (skyColor == RGB(135, 206, 250)) ? RGB(25, 25, 112) : RGB(135, 206, 250);
            InvalidateRect(hwnd, nullptr, TRUE);
            break;

        case ID_40003: // "Hide"
            hideClouds = !hideClouds;
            InvalidateRect(hwnd, nullptr, TRUE);
            break;

        case ID_40004: // "About program"
            MessageBox(hwnd, L"Laba 3 Task 2\nVariant 16\nAuthor: WW", L"About", MB_OK | MB_ICONINFORMATION);
            break;

        case ID_40005: // "Exit"
            DestroyWindow(hwnd);
            break;
        }
        return 0;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(hwnd, &ps);

        //сцена малюється тільки якщо showImage == true
        if (showImage) {
            RECT rect;
            GetClientRect(hwnd, &rect);
            DrawScene(dc, rect.right, rect.bottom, skyColor, hideClouds);
        }

        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_LBUTTONDOWN: {
        MessageBox(hwnd, L"Stop Clicking", L"Message WM_LBUTTONDOWN", MB_OK | MB_ICONINFORMATION);
        return 0;
    }
    case WM_KEYDOWN: {
        if (wParam == VK_ESCAPE) {
            DestroyWindow(hwnd);
        }
        return 0;
    }
    case WM_SIZE: {
        // перемальовка при зміні розміру, тільки якщо картинка показана
        if (showImage) {
            InvalidateRect(hwnd, nullptr, TRUE);
        }
        return 0;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
        return 0;
    }
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

// =======================================================================
// Головна функція
// =======================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Variant16App";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); // підключення меню

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Laba 3 Task 2",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 900, 600,
        nullptr, nullptr, hInstance, nullptr);

    if (hwnd == nullptr) return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG message = { };
    while (GetMessage(&message, nullptr, 0, 0) > 0) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    return (int)message.wParam;
}