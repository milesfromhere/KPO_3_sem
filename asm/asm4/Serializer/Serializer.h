#pragma once
#include "stdafx.h"

// ����� Serializer: ��������� ���������������� ��� ������������ ������ � ������ �� � ����
class Serializer {
private:
    std::ofstream file;              // ����� ��� ������ ������ � ����
    unsigned char boolMarker;        // ������ ��� bool
    unsigned char int16Marker;       // ������ ��� int16_t
    unsigned char boolLength;        // ����� bool
    unsigned char int16Length;       // ����� int16_t
    bool boolValue;                  // ��������������� �������� bool
    int16_t int16Value;              // ��������������� �������� int16_t

public:
    // �����������: �������������� �������� � �������
    Serializer(bool boolValue, int16_t int16Value)
        : boolMarker(0x01), int16Marker(0x02), boolLength(sizeof(bool)), int16Length(sizeof(int16_t)) {
        this->boolValue = boolValue;
        this->int16Value = int16Value;
    }

    // ����� ��� ������������ ������
    void SerializeData();
};

