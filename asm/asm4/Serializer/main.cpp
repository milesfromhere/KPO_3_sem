#include "stdafx.h"

int main() {
    setlocale(LC_ALL, "ru");
    bool b;
    int16_t i;

    cout << "������� �������� ��� bool (0 ��� 1): ";
    cin >> b;

    cout << "������� �������� ��� �������������� �������� (2 �����): ";
    cin >> i;

    Serializer serializer(b, i);
    serializer.SerializeData();

    return 0;
}
