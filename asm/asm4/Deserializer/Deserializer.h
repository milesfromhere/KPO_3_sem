#pragma once
#include "stdafx.h"

// ����� Deserializer: ��������� ���������������� ��� �������������� ������ � �������������� �� � ������������ ���
class Deserializer {
private:
    std::ifstream file;         // ����� ��� ������ ������ �� �����
    std::ofstream fileAsm;      // ����� ��� ������ ������������� ���� � ����
    bool boolValue;             // ����������������� �������� bool
    int16_t int16Value;         // ����������������� �������� int16_t

public:
    // �����������
    Deserializer() : boolValue(false), int16Value(0) {}

    // ����� ��� �������������� ������
    void DeserializeData();

    // ����� ��� �������������� ������ � ������������ ���
    void ConvertToAssembler();
};

