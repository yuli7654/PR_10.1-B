#pragma once
#include <string>

// Спеціальність студента
enum Spec
{
    KOMP_NAUKY,          // Комп'ютерні науки
    INFORMATYKA,         // Інформатика
    MATEM_EKONOMIKA,     // Математика та економіка
    FIZYKA_INFORMATYKA,  // Фізика та інформатика
    TRUDOVE_NAVCHANNYA   // Трудове навчання
};

const int SPEC_COUNT = 5;

// Предмети (індекси масиву лічильників оцінок)
enum Predmet
{
    FIZYKA,
    MATEMATYKA,
    PROGRAMUVANNYA,
    CHYSELNI_METODY,
    PEDAGOGIKA
};

const int PREDMET_COUNT = 5;

extern const std::string specStr[SPEC_COUNT];       // назви спеціальностей
extern const std::string predmetStr[PREDMET_COUNT]; // назви предметів

struct Student
{
    std::string prizv;   // прізвище
    int         kurs;    // курс
    Spec        spec;    // спеціальність
    int         fizyka;      // оцінка з фізики
    int         matematyka;  // оцінка з математики
    union                    // третя оцінка залежить від спеціальності
    {
        int programuvannya;  // KOMP_NAUKY
        int chyslMetody;     // INFORMATYKA
        int pedagogika;      // MATEM_EKONOMIKA, FIZYKA_INFORMATYKA, TRUDOVE_NAVCHANNYA
    };
};

// Створення масиву: введення даних студентів з клавіатури
void Create(Student* s, const int N);

// Виведення масиву у вигляді таблиці
void Print(const Student* s, const int N);

// Повертає третю оцінку студента (з програмування, чисельних методів або педагогіки)
int ThirdGrade(const Student& st);

// Повертає середній бал студента (по трьох оцінках)
double Average(const Student& st);

// Завдання 1. Повертає індекс студента з найменшим середнім балом
// (при однакових балах – перший з них); -1, якщо масив порожній
int FindMinAverageIndex(const Student* s, const int N);

// Завдання 2. Обчислює кількість оцінок «задовільно» (3) з кожного предмету;
// результат – у масиві counts[PREDMET_COUNT], індекс – значення перелічення Predmet
void CountSatisfactory(const Student* s, const int N, int counts[PREDMET_COUNT]);

// Виведення кількості оцінок «задовільно» з кожного предмету
void PrintSatisfactory(const int counts[PREDMET_COUNT]);
