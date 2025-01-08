#include "FST.h"
#include <iostream>
#include <string>
#include <cstdarg>  // Для работы с variadic arguments

namespace FST
{
    // Конструктор структуры RELATION. 
    // Устанавливает символ (c) и номер состояния, в которое происходит переход (nn).
    RELATION::RELATION(char c, short nn)
    {
        symbol = c;
        nnode = nn;
    }

    // Конструктор по умолчанию для структуры NODE.
    // Инициализирует количество отношений как 0 и устанавливает пустой указатель на массив отношений.
    NODE::NODE()
    {
        n_relation = 0;
        relations = nullptr;
    }

    // Конструктор для структуры NODE с variadic arguments.
    // Принимает количество отношений (n) и список отношений (RELATION).
    NODE::NODE(short n, RELATION rel, ...)
    {
        n_relation = n;
        relations = new RELATION[n];  // Создание массива для хранения отношений.

        va_list args;
        va_start(args, rel);  // Инициализация списка аргументов.
        relations[0] = rel;  // Первый аргумент уже передан напрямую.
        for (short i = 1; i < n; i++)
        {
            relations[i] = va_arg(args, RELATION);  // Получение последующих аргументов.
        }
        va_end(args);  // Завершение работы с аргументами.
    }

    // Конструктор для структуры FST.
    // Принимает строку (s), количество состояний (ns) и список состояний (NODE).
    FST::FST(const char* s, short ns, NODE n, ...)
    {
        string = s;  // Сохраняем строку, которую будем проверять.
        nstates = ns;  // Количество состояний.
        nodes = new NODE[ns];  // Массив узлов (состояний автомата).

        va_list args;
        va_start(args, n);  // Инициализация списка аргументов.
        nodes[0] = n;  // Первый узел передан напрямую.
        for (int k = 1; k < ns; k++)
        {
            nodes[k] = va_arg(args, NODE);  // Получение последующих узлов.
        }
        va_end(args);  // Завершение работы с аргументами.

        rstates = new short[nstates];  // Массив для отслеживания текущих состояний.
        memset(rstates, 0xff, sizeof(short) * nstates);  // Инициализация массива значением 0xff (отсутствие состояния).
        rstates[0] = 0;  // Начальное состояние - состояние 0.
        position = -1;  // Текущая позиция в строке.
    }

    // Деструктор для структуры FST.
    // Освобождает динамически выделенную память для узлов и состояний.
    FST::~FST()
    {
        delete[] nodes;  // Удаляем массив узлов.
        delete[] rstates;  // Удаляем массив состояний.
    }

    // Функция step - выполняет один шаг автомата.
    // Применяет текущий символ строки к автомату и обновляет состояния.
    bool step(FST& fst, short*& rstates)
    {
        bool rc = false;  // Флаг успешности шага.
        std::swap(rstates, fst.rstates);  // Меняем местами текущие и предыдущие состояния.

        // Проходим по всем состояниям автомата.
        for (short i = 0; i < fst.nstates; i++)
        {
            // Проверяем, соответствует ли состояние текущей позиции.
            if (rstates[i] == fst.position)
            {
                // Проверяем все возможные переходы из текущего состояния.
                for (short j = 0; j < fst.nodes[i].n_relation; j++)
                {
                    // Если символ соответствует символу строки на текущей позиции.
                    if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
                    {
                        // Обновляем состояние в rstates и переходим на следующую позицию в строке.
                        fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
                        rc = true;  // Шаг успешен.
                    }
                }
            }
        }

        return rc;  // Возвращаем успешность шага.
    }

    // Функция execute - выполняет полный цикл автомата для строки.
    bool execute(FST& fst)
    {
        short* rstates = new short[fst.nstates];  // Локальная копия состояний.
        memset(rstates, 0xff, sizeof(short) * fst.nstates);  // Инициализация состояний значением 0xff.
        short lstring = strlen(fst.string);  // Длина строки.
        bool rc = true;  // Флаг успешности выполнения.

        // Проходим по каждому символу строки.
        for (short i = 0; i < lstring && rc; i++)
        {
            fst.position++;  // Переходим к следующему символу.
            rc = step(fst, rstates);  // Выполняем шаг автомата.
        }

        delete[] rstates;  // Освобождаем память для локальной копии состояний.
        // Проверяем, находится ли автомат в конечном состоянии и вся строка пройдена.
        return (fst.rstates[fst.nstates - 1] == lstring);
    }
}
