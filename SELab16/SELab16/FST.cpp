#include "FST.h"
#include <iostream>
#include <string>
#include <cstdarg>  // ��� ������ � variadic arguments

namespace FST
{
    // ����������� ��������� RELATION. 
    // ������������� ������ (c) � ����� ���������, � ������� ���������� ������� (nn).
    RELATION::RELATION(char c, short nn)
    {
        symbol = c;
        nnode = nn;
    }

    // ����������� �� ��������� ��� ��������� NODE.
    // �������������� ���������� ��������� ��� 0 � ������������� ������ ��������� �� ������ ���������.
    NODE::NODE()
    {
        n_relation = 0;
        relations = nullptr;
    }

    // ����������� ��� ��������� NODE � variadic arguments.
    // ��������� ���������� ��������� (n) � ������ ��������� (RELATION).
    NODE::NODE(short n, RELATION rel, ...)
    {
        n_relation = n;
        relations = new RELATION[n];  // �������� ������� ��� �������� ���������.

        va_list args;
        va_start(args, rel);  // ������������� ������ ����������.
        relations[0] = rel;  // ������ �������� ��� ������� ��������.
        for (short i = 1; i < n; i++)
        {
            relations[i] = va_arg(args, RELATION);  // ��������� ����������� ����������.
        }
        va_end(args);  // ���������� ������ � �����������.
    }

    // ����������� ��� ��������� FST.
    // ��������� ������ (s), ���������� ��������� (ns) � ������ ��������� (NODE).
    FST::FST(const char* s, short ns, NODE n, ...)
    {
        string = s;  // ��������� ������, ������� ����� ���������.
        nstates = ns;  // ���������� ���������.
        nodes = new NODE[ns];  // ������ ����� (��������� ��������).

        va_list args;
        va_start(args, n);  // ������������� ������ ����������.
        nodes[0] = n;  // ������ ���� ������� ��������.
        for (int k = 1; k < ns; k++)
        {
            nodes[k] = va_arg(args, NODE);  // ��������� ����������� �����.
        }
        va_end(args);  // ���������� ������ � �����������.

        rstates = new short[nstates];  // ������ ��� ������������ ������� ���������.
        memset(rstates, 0xff, sizeof(short) * nstates);  // ������������� ������� ��������� 0xff (���������� ���������).
        rstates[0] = 0;  // ��������� ��������� - ��������� 0.
        position = -1;  // ������� ������� � ������.
    }

    // ���������� ��� ��������� FST.
    // ����������� ����������� ���������� ������ ��� ����� � ���������.
    FST::~FST()
    {
        delete[] nodes;  // ������� ������ �����.
        delete[] rstates;  // ������� ������ ���������.
    }

    // ������� step - ��������� ���� ��� ��������.
    // ��������� ������� ������ ������ � �������� � ��������� ���������.
    bool step(FST& fst, short*& rstates)
    {
        bool rc = false;  // ���� ���������� ����.
        std::swap(rstates, fst.rstates);  // ������ ������� ������� � ���������� ���������.

        // �������� �� ���� ���������� ��������.
        for (short i = 0; i < fst.nstates; i++)
        {
            // ���������, ������������� �� ��������� ������� �������.
            if (rstates[i] == fst.position)
            {
                // ��������� ��� ��������� �������� �� �������� ���������.
                for (short j = 0; j < fst.nodes[i].n_relation; j++)
                {
                    // ���� ������ ������������� ������� ������ �� ������� �������.
                    if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
                    {
                        // ��������� ��������� � rstates � ��������� �� ��������� ������� � ������.
                        fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
                        rc = true;  // ��� �������.
                    }
                }
            }
        }

        return rc;  // ���������� ���������� ����.
    }

    // ������� execute - ��������� ������ ���� �������� ��� ������.
    bool execute(FST& fst)
    {
        short* rstates = new short[fst.nstates];  // ��������� ����� ���������.
        memset(rstates, 0xff, sizeof(short) * fst.nstates);  // ������������� ��������� ��������� 0xff.
        short lstring = strlen(fst.string);  // ����� ������.
        bool rc = true;  // ���� ���������� ����������.

        // �������� �� ������� ������� ������.
        for (short i = 0; i < lstring && rc; i++)
        {
            fst.position++;  // ��������� � ���������� �������.
            rc = step(fst, rstates);  // ��������� ��� ��������.
        }

        delete[] rstates;  // ����������� ������ ��� ��������� ����� ���������.
        // ���������, ��������� �� ������� � �������� ��������� � ��� ������ ��������.
        return (fst.rstates[fst.nstates - 1] == lstring);
    }
}
