#pragma once

// SocketUser command target

class SocketUser : public CSocket
{
protected:
	CObList* mp_user_list;					// 상위서버의 연결리스트 주소를 생성자로 받아서 해제하는 클라이언트만 삭제하기
	char m_flag_header = 1;				// 헤더를 처리할 상황인지 알려주는 플래그
	unsigned int m_data_size;

public:
	SocketUser(CObList* ap_user_list);
	virtual ~SocketUser();

	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


