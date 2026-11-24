
#include "Student.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

const string specStr[SPEC_COUNT] =
{
    "Комп'ютерні науки", "Інформатика", "Математика та економіка",
    "Фізика та інформатика", "Трудове навчання"
};

const string predmetStr[PREDMET_COUNT] =
{
    "фізика", "математика", "програмування", "чисельні методи", "педагогіка"
};

namespace
{
    // Кількість символів (а не байтів) у рядку UTF-8 – для рівного вирівнювання кирилиці
    int Len(const string& s)
    {
        int n = 0;
        for (unsigned char c : s)
            if ((c & 0xC0) != 0x80)
                n++;
        return n;
    }

    // Рядок, доповнений пробілами праворуч до ширини w
    string PadRight(const string& s, const int w)
    {
        int d = w - Len(s);
        return s + string(d > 0 ? d : 0, ' ');
    }

    // Рядок, доповнений пробілами ліворуч до ширини w
    string PadLeft(const string& s, const int w)
    {
        int d = w - Len(s);
        return string(d > 0 ? d : 0, ' ') + s;
    }

    // Рядок, відцентрований у ширині w
    string Center(const string& s, const int w)
    {
        int d = w - Len(s);
        if (d <= 0) return s;
        return string(d / 2, ' ') + s + string(d - d / 2, ' ');
    }

    // Введення цілого числа в діапазоні [lo; hi] з повторенням при помилці
    int ReadInt(const string& prompt, const int lo, const int hi)
    {
        int x;
        while (true)
        {
            cout << prompt;
            if (cin >> x && x >= lo && x <= hi)
                return x;
            cout << "     Помилка! Введіть ціле число від " << lo << " до " << hi << "." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void Create(Student* s, const int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очищуємо буфер вводу
        do
        {
            cout << "     прізвище: ";
            getline(cin, s[i].prizv);
        } while (s[i].prizv.empty());

        s[i].kurs = ReadInt("     курс (1-6): ", 1, 6);

        cout << "     спеціальність:" << endl;
        for (int k = 0; k < SPEC_COUNT; k++)
            cout << "        " << k << " - " << specStr[k] << endl;
        s[i].spec = (Spec)ReadInt("     вибір (0-4): ", 0, SPEC_COUNT - 1);

        s[i].fizyka = ReadInt("     оцінка з фізики (1-5): ", 1, 5);
        s[i].matematyka = ReadInt("     оцінка з математики (1-5): ", 1, 5);

        switch (s[i].spec)
        {
        case KOMP_NAUKY:
            s[i].programuvannya = ReadInt("     оцінка з програмування (1-5): ", 1, 5);
            break;
        case INFORMATYKA:
            s[i].chyslMetody = ReadInt("     оцінка з чисельних методів (1-5): ", 1, 5);
            break;
        default:
            s[i].pedagogika = ReadInt("     оцінка з педагогіки (1-5): ", 1, 5);
            break;
        }
        cout << endl;
    }
}

void Print(const Student* s, const int N)
{
    // ширини клітинок таблиці
    const int w[9] = { 4, 16, 6, 25, 8, 11, 14, 16, 11 };
    const string head[9] = { "№", "Прізвище", "Курс", "Спеціальність", "Фізика",
                             "Математика", "Програмування", "Чисельні методи", "Педагогіка" };

    int total = 1;
    for (int k = 0; k < 9; k++)
        total += w[k] + 1;

    const string eq(total, '='), dash(total, '-');

    cout << eq << endl;
    cout << "|" << Center("Список студентів", total - 2) << "|" << endl;
    cout << eq << endl;

    cout << "|";
    for (int k = 0; k < 9; k++)
        cout << Center(head[k], w[k]) << "|";
    cout << endl << dash << endl;

    for (int i = 0; i < N; i++)
    {
        // порожні клітинки для оцінок, які студент не має
        string prog, chysl, ped;
        switch (s[i].spec)
        {
        case KOMP_NAUKY:   prog = to_string(s[i].programuvannya); break;
        case INFORMATYKA:  chysl = to_string(s[i].chyslMetody);    break;
        default:           ped = to_string(s[i].pedagogika);     break;
        }

        cout << "|" << PadLeft(to_string(i + 1), w[0] - 1) << " "
            << "|" << " " << PadRight(s[i].prizv, w[1] - 1)
            << "|" << Center(to_string(s[i].kurs), w[2])
            << "|" << " " << PadRight(specStr[s[i].spec], w[3] - 1)
            << "|" << Center(to_string(s[i].fizyka), w[4])
            << "|" << Center(to_string(s[i].matematyka), w[5])
            << "|" << Center(prog, w[6])
            << "|" << Center(chysl, w[7])
            << "|" << Center(ped, w[8])
            << "|" << endl;
    }
    cout << eq << endl << endl;
}

int ThirdGrade(const Student& st)
{
    // читаємо саме те поле об'єднання, яке було записане для цієї спеціальності
    switch (st.spec)
    {
    case KOMP_NAUKY:  return st.programuvannya;
    case INFORMATYKA: return st.chyslMetody;
    default:          return st.pedagogika;
    }
}

namespace
{
    // Сума трьох оцінок студента (цілі числа – без похибок порівняння дійсних)
    int GradeSum(const Student& st)
    {
        return st.fizyka + st.matematyka + ThirdGrade(st);
    }
}

double Average(const Student& st)
{
    return GradeSum(st) / 3.0;
}

int FindMinAverageIndex(const Student* s, const int N)
{
    if (N <= 0)
        return -1;

    int iMin = 0;
    for (int i = 1; i < N; i++)         // послідовний пошук мінімуму
        if (GradeSum(s[i]) < GradeSum(s[iMin]))
            iMin = i;

    return iMin;
}

void CountSatisfactory(const Student* s, const int N, int counts[PREDMET_COUNT])
{
    for (int k = 0; k < PREDMET_COUNT; k++)
        counts[k] = 0;

    for (int i = 0; i < N; i++)
    {
        if (s[i].fizyka == 3)     counts[FIZYKA]++;
        if (s[i].matematyka == 3) counts[MATEMATYKA]++;

        if (ThirdGrade(s[i]) == 3)
        {
            switch (s[i].spec)
            {
            case KOMP_NAUKY:  counts[PROGRAMUVANNYA]++;  break;
            case INFORMATYKA: counts[CHYSELNI_METODY]++; break;
            default:          counts[PEDAGOGIKA]++;      break;
            }
        }
    }
}

void PrintSatisfactory(const int counts[PREDMET_COUNT])
{
    cout << "Кількість оцінок «задовільно» з кожного предмету:" << endl;
    for (int k = 0; k < PREDMET_COUNT; k++)
        cout << "   " << PadRight(predmetStr[k], 16) << ": " << counts[k] << endl;
}