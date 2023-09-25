#pragma once
#pragma pack(push, 1)

// 휴대용 리더기 데이터
struct ReaderData
{
    char serial_no[45];     // 유도탄 시리얼번호
    char sensor_sn[45];             // 센서의 시리얼번호
    char datetime[20];    // DATETIME (YYYY-MM-DD HH:MM:SS 형식)
    float temp;          // 온도
    int humi;              // 습도
    float vib;              // 진동가속도
    float lat;              // 위도
    float lon;              // 경도
    float reader_acc;       // 리더기 분석값
};

// 전술교전망 연동장치 데이터
struct BitData
{

};

// 유도탄 생산데이터(입력용)
struct QIMData
{

};

// 시각화 통합서버에서 보여줄 표
struct TableData
{
    
};

#pragma pack(pop)