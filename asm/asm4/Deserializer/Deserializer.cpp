#include "stdafx.h"

// ����� Deserializer::DeserializeData(): ��������� �������������� ������ �� �����
void Deserializer::DeserializeData() {
    file = ifstream("../Serializer/bin.bin", ios::binary);

    if (!file.is_open()) {
        cout << "������: �� ������� ������� ���� ��� ������!" << endl;
        return;
    }

    unsigned char marker, length;

    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(&marker), sizeof(marker));
        file.read(reinterpret_cast<char*>(&length), sizeof(length));

        if (file.eof()) break;

        if (marker == 0x01) {
            file.read(reinterpret_cast<char*>(&boolValue), length);
        }
        else if (marker == 0x02) {
            file.read(reinterpret_cast<char*>(&int16Value), length);
        }
    }

    file.close();
    cout << "������ ���������������: bool = " << boolValue << ", int16 = " << int16Value << endl;
}

// ����� Deserializer::ConvertToAssembler(): ����������� ����������������� ������ � ��� �� ����������
void Deserializer::ConvertToAssembler() {
    fileAsm = ofstream("C:/Users/nikit/OneDrive/������� ����/���/asm/asm4/SE_Asm04/asm4.asm");

    if (!fileAsm.is_open()) {
        cout << "������: �� ������� ������� ���� ��� ������ ASM!" << endl;
        return;
    }

    fileAsm << ASM_HEAD;
    fileAsm << "BOOLF DB " << (boolValue ? 1 : 0) << endl;
    fileAsm << "INT16F DW " << int16Value << endl;
    fileAsm << ASM_FOOTER;

    fileAsm.close();
    cout << "������������ ��� ������� ������� � ���� asm4.asm!" << endl;
}
