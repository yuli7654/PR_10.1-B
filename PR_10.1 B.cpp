#include <iostream>
#include <iomanip>
#include <limits>

#ifdef _WIN32
#include <Windows.h>   // забезпечення відображення кирилиці
#endif

#include "student.h"

using namespace std;

int main()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);        // кодування UTF-8 для вводу
    SetConsoleOutputCP(CP_UTF8);  // кодування UTF-8 для виводу
#endif

    int N;
    do
    {
        cout << "Введіть кількість студентів N: ";
        if (!(cin >> N))
        {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            N = 0;
        }
    } while (N <= 0);

    Student* s = new Student[N];

    Create(s, N);
    Print(s, N);

    // Завдання 1
    int iMin = FindMinAverageIndex(s, N);
    cout << "Студент з найменшим середнім балом: " << s[iMin].prizv
        << " (середній бал " << fixed << setprecision(2) << Average(s[iMin]) << ")"
        << endl << endl;

    // Завдання 2
    int counts[PREDMET_COUNT];
    CountSatisfactory(s, N, counts);
    PrintSatisfactory(counts);

    delete[] s;
    return 0;
}
