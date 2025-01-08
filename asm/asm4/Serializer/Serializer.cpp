#include "stdafx.h"

// ����� Serializer::SerializeData(): ��������� ������������ ������ � ������ �� � �������� ����
void Serializer::SerializeData() {
    file = ofstream("bin.bin", ios::binary);
    //file = ofstream("E:\KPO\SE_Asm04\SE_Asm04\\bin.bin");
    //ofstream file("E:\\KPO\\SE_Asm04\\SE_Asm04\\bin.bin", ios::binary);
    if (!file.is_open()) {
        cout << "������: �� ������� ������� ���� ��� ������!" << endl;
        return;
    }

    // ������������ bool
    file.write(reinterpret_cast<char*>(&boolMarker), sizeof(boolMarker));
    file.write(reinterpret_cast<char*>(&boolLength), sizeof(boolLength));
    file.write(reinterpret_cast<char*>(&boolValue), boolLength);

    // ������������ int16_t
    file.write(reinterpret_cast<char*>(&int16Marker), sizeof(int16Marker));
    file.write(reinterpret_cast<char*>(&int16Length), sizeof(int16Length));
    file.write(reinterpret_cast<char*>(&int16Value), int16Length);

    //file  << boolValue << "\n";
    //file  << int16Value << "\n";


    file.close();
    cout << "������ ������� ������������� � ���� bin.bin!" << endl;
}
