#pragma once
#pragma pack(push, 1)

// �޴�� ������ ������
struct ReaderData
{
    char serial_no[45];     // ����ź �ø����ȣ
    char sensor_sn[45];             // ������ �ø����ȣ
    char datetime[20];    // DATETIME (YYYY-MM-DD HH:MM:SS ����)
    float temp;          // �µ�
    int humi;              // ����
    float vib;              // �������ӵ�
    float lat;              // ����
    float lon;              // �浵
    float reader_acc;       // ������ �м���
};

// ���������� ������ġ ������
struct BitData
{

};

// ����ź ���굥����(�Է¿�)
struct QIMData
{

};

// �ð�ȭ ���ռ������� ������ ǥ
struct TableData
{
    
};

#pragma pack(pop)