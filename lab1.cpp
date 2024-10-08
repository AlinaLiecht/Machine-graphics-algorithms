#include <graphics.h>
#include <cmath>
#include <windows.h>

// Функция для отрисовки Пифагорова дерева
// depth - текущая глубина рекурсии
// x_A, y_A - координаты точки A, одной из вершин квадрата
// square_side_length - длина стороны квадрата
// fi_deg - угол наклона квадрата относительно горизонтали (в градусах)
// alpha_deg - угол наклона крыши (в градусах)
void pifagor(int depth, int x_A, int y_A, int square_side_length, double fi_deg, double alpha_deg) {
    // Базовый случай: если глубина рекурсии 0, прекратить дальнейшие вычисления
    if (depth == 0) return;

    // Преобразование углов из градусов в радианы для использования в тригонометрических функциях
    double fi_rad = fi_deg * M_PI / 180.0;    // Угол наклона основания квадрата
    double alpha_rad = alpha_deg * M_PI / 180.0; // Угол наклона крыши (для построения новых квадратов)

    // Вычисление координат вершин квадрата ABCD

    // Вершина B: находим точку справа от A на длину стороны квадрата под углом fi_rad
    double x_B = x_A + square_side_length * cos(fi_rad);
    double y_B = y_A - square_side_length * sin(fi_rad);

    // Вершина C: находим точку сверху от B (поворот на 90 градусов от B)
    double x_C = x_B - square_side_length * sin(fi_rad);
    double y_C = y_B - square_side_length * cos(fi_rad);

    // Вершина D: аналогично C, находим точку слева от A (поворот на 90 градусов)
    double x_D = x_A - square_side_length * sin(fi_rad);
    double y_D = y_A - square_side_length * cos(fi_rad);

    // Отрисовка квадрата ABCD
    line(x_A, y_A, x_B, y_B); // Линия AB
    line(x_B, y_B, x_C, y_C); // Линия BC
    line(x_C, y_C, x_D, y_D); // Линия CD
    line(x_D, y_D, x_A, y_A); // Линия DA

    // Вычисление длин сторон для новых квадратов, которые "растут" на сторонах CD и CE

    // Сторона CE: высчитывается как произведение длины текущего квадрата на sin(alpha_rad),
    // где alpha_rad — угол наклона крыши
    double CE = square_side_length * sin(alpha_rad);

    // Сторона DE: аналогично, но длина стороны DE — это произведение длины текущего квадрата
    // на cos(alpha_rad)
    double DE = square_side_length * cos(alpha_rad);

    // Вершина E: вычисляем точку, относительно вершины D, для формирования новых квадратов
    // Точка смещается на расстояние DE под углом fi_rad + alpha_rad
    double x_E = x_D + DE * cos(fi_rad + alpha_rad);
    double y_E = y_D - DE * sin(fi_rad + alpha_rad);

    // Отрисовка новых линий между вершинами C, D и E
    line(x_C, y_C, x_E, y_E); // Линия CE
    line(x_E, y_E, x_D, y_D); // Линия ED

    // Подготовка углов для рекурсивного построения следующих квадратов

    // Угол для квадрата на стороне DE. Он увеличивается на alpha_deg, так как это угол наклона "крыши".
    double fi_deg_DE = fi_deg + alpha_deg;

    // Угол для квадрата на стороне CE. Угол CE уменьшается на 90 градусов, так как это вертикальная сторона,
    // относительно DE.
    double fi_deg_CE = fi_deg + alpha_deg - 90;

    // Рекурсивные вызовы для следующих квадратов на сторонах DE и CE
    // Первый квадрат растет на стороне DE
    pifagor(depth - 1, (int)x_D, (int)y_D, (int)DE, fi_deg_DE, alpha_deg);

    // Второй квадрат растет на стороне CE
    pifagor(depth - 1, (int)x_E, (int)y_E, (int)CE, fi_deg_CE, alpha_deg);
}

int main() {
    // Получение размеров экрана для полноэкранного режима
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Инициализация графического окна на весь экран
    initwindow(screenWidth, screenHeight, "Дерево Пифагора - Полноэкранный режим", -3, -3);

    // Начальная точка привязки "домика" (точка A)
    int x0 = screenWidth / 2;       // Центр по горизонтали
    int y0 = screenHeight - 200;    // Отступ от нижнего края

    // Параметры фрактала
    int n = 10;          // Глубина рекурсии (чем больше значение, тем более детализированное дерево)
    int a = 100;         // Длина основания начального квадрата (размер квадрата)
    double fi = 0.0;   // Угол наклона первого квадрата относительно горизонтали (нулевой угол - квадрат стоит прямо)
    double alpha = 25.0; // Угол наклона крыши квадрата (угол наклона фрактала, наклон квадратов относительно вертикали)

    // Вызов функции для начала построения дерева Пифагора
    pifagor(n, x0, y0, a, fi, alpha);

    // Ожидание нажатия клавиши для закрытия графического окна
    getch();
    closegraph(); // Закрытие графического окна
    return 0;
}
