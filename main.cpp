#include <windows.h>
#include <string>

// id елементів керування
#define ID_EDIT_X 101
#define ID_EDIT_Y 102
#define ID_BUTTON 103
#define ID_STATIC_RESULT 104

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEXA wc = { sizeof(WNDCLASSEXA), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0,
                       hInstance, LoadIcon(NULL, IDI_APPLICATION), LoadCursor(NULL, IDC_ARROW),
                       (HBRUSH)(COLOR_WINDOW + 1), NULL, "CalcClass", LoadIcon(NULL, IDI_APPLICATION) };
    RegisterClassExA(&wc);

    HWND hwnd = CreateWindowExA(0, "CalcClass", "Laba 3 - Task 1",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 350, 250,
        NULL, NULL, hInstance, NULL);
    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessageA(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static HWND hEditX, hEditY, hButton, hResult;

    switch (message) {
    case WM_CREATE: {
        HINSTANCE hInst = ((LPCREATESTRUCT)lParam)->hInstance;

        //поля введення для x та y 
        hEditX = CreateWindowExA(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
            80, 30, 100, 25, hwnd, (HMENU)ID_EDIT_X, hInst, NULL);
        hEditY = CreateWindowExA(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
            80, 70, 100, 25, hwnd, (HMENU)ID_EDIT_Y, hInst, NULL);

        // кнопка розрахунку
        hButton = CreateWindowExA(0, "BUTTON", "Calculate", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            80, 110, 100, 30, hwnd, (HMENU)ID_BUTTON, hInst, NULL);

        // поле для результату
        hResult = CreateWindowExA(0, "STATIC", "Result: ", WS_CHILD | WS_VISIBLE,
            30, 160, 250, 25, hwnd, (HMENU)ID_STATIC_RESULT, hInst, NULL);
        break;
    }
    case WM_COMMAND: {
        // пперевіка чи натиснута саме наша кнопка
        if (LOWORD(wParam) == ID_BUTTON) {
            char bufX[50], bufY[50];
            GetWindowTextA(hEditX, bufX, sizeof(bufX));
            GetWindowTextA(hEditY, bufY, sizeof(bufY));

            try {
                double x = std::stod(bufX);
                double y = std::stod(bufY);

                std::string resStr = "Result: ";

                if (x <= 0) {
                    resStr += "0";
                }
                else if (x > y) {
                    resStr += std::to_string((int)(x - 1));
                }
                else {
                    resStr += "undefined";
                }

                SetWindowTextA(hResult, resStr.c_str());
            }
            catch (...) {
                //некоректний інпут
                SetWindowTextA(hResult, "Input Error");
            }
        }
        break;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        TextOutA(hdc, 40, 35, "x =", 3);
        TextOutA(hdc, 40, 75, "y =", 3);
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcA(hwnd, message, wParam, lParam);
    }
    return 0;
}