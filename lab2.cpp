#include <graphics.h>
#include <cmath>
#include <windows.h>

// Функция для построения линии с использованием алгоритма Брезенхейма
void myline(int x1, int y1, int x2, int y2, int color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (true) {
        putpixel(x1, y1, color);

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

// Функция для построения окружности с использованием алгоритма Брезенхейма
void mycircle(int x0, int y0, int r, int color) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while (y >= x) {
        // Отображаем все восемь симметричных точек
        putpixel(x0 + x, y0 + y, color);
        putpixel(x0 - x, y0 + y, color);
        putpixel(x0 + x, y0 - y, color);
        putpixel(x0 - x, y0 - y, color);
        putpixel(x0 + y, y0 + x, color);
        putpixel(x0 - y, y0 + x, color);
        putpixel(x0 + y, y0 - x, color);
        putpixel(x0 - y, y0 - x, color);

        x++;

        if (d > 0) {
            y--;
            d += 4 * (x - y) + 10;
        }
        else {
            d += 4 * x + 6;
        }
    }
}

// Обновленная функция pifagor с использованием myline
void pifagor(int current_fractal_depth, int xA, int yA, int square_side_length, double fi_deg, double alpha_deg) {
    if (current_fractal_depth == 0) return;

    double fi_rad = fi_deg * M_PI / 180.0;
    double alpha_rad = alpha_deg * M_PI / 180.0;

    // Вычисление координат точек домика
    double xB = xA + square_side_length * cos(fi_rad);
    double yB = yA - square_side_length * sin(fi_rad);

    double xC = xB - square_side_length * sin(fi_rad);
    double yC = yB - square_side_length * cos(fi_rad);

    double xD = xA - square_side_length * sin(fi_rad);
    double yD = yA - square_side_length * cos(fi_rad);

    // Рисование сторон домика с использованием myline
    myline(xA, yA, (int)xB, (int)yB, WHITE);
    myline((int)xB, (int)yB, (int)xC, (int)yC, WHITE);
    myline((int)xC, (int)yC, (int)xD, (int)yD, WHITE);
    myline((int)xD, (int)yD, xA, yA, WHITE);

    // Вычисление координат вершины крыши
    double CE = square_side_length * sin(alpha_rad);
    double DE = square_side_length * cos(alpha_rad);

    double xE = xD + DE * cos(fi_rad + alpha_rad);
    double yE = yD - DE * sin(fi_rad + alpha_rad);

    // Рисование крыши
    myline((int)xC, (int)yC, (int)xE, (int)yE, WHITE);
    myline((int)xE, (int)yE, (int)xD, (int)yD, WHITE);

    // Обновление углов для рекурсивных вызовов
    double fi_deg_DE = fi_deg + alpha_deg;
    double fi_deg_CE = fi_deg + alpha_deg - 90;

    // Рекурсивные вызовы для построения двух новых домиков
    pifagor(current_fractal_depth - 1, (int)xD, (int)yD, (int)DE, fi_deg_DE, alpha_deg);
    pifagor(current_fractal_depth - 1, (int)xE, (int)yE, (int)CE, fi_deg_CE, alpha_deg);
}


 // Пример использования функций myline и mycircle в main

//int main() {
//    // Инициализация графического режима
//    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
//    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
//
//    initwindow(screenWidth, screenHeight, "Алгоритмы Брезенхейма: Линия и Окружность", -3, -3);
//
//    // Пример использования myline
//    myline(100, 100, 400, 300, WHITE);   // Белая линия
//    myline(400, 100, 100, 300, RED);     // Красная линия
//
//    // Пример использования mycircle
//    mycircle(screenWidth / 2, screenHeight / 2, 100, BLUE);   // Синяя окружность
//    mycircle(screenWidth / 2, screenHeight / 2, 150, GREEN);  // Зеленая окружность
//
//    // Ожидание нажатия клавиши
//    getch();
//    closegraph();
//
//    return 0;
//}


// Пример использования обновленной функции pifagor в main

//int main() {
//    // Инициализация графического режима
//    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
//    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
//
//    initwindow(screenWidth, screenHeight, "Фрактал Дерево Пифагора", -3, -3);
//
//    // Построение фрактала «Дерево Пифагора» с использованием myline
//    int x_A = screenWidth / 2;
//    int y_A = screenHeight - 200;
//
//    int max_fractal_depth = 10;
//    int square_side_length = 100;
//    double fi_deg = 0.0;
//    double alpha_deg = 25.0;
//
//    pifagor(max_fractal_depth, x_A, y_A, square_side_length, fi_deg, alpha_deg);
//
//    // Ожидание нажатия клавиши
//    getch();
//    closegraph();
//
//    return 0;
//}


