#ifndef _TW_DOUBLE_LINKED_LIST_H_
#define _TW_DOUBLE_LINKED_LIST_H_

/*
    이 클래스는 더블 링크드 리스트를 구현한 것입니다.
    MFC의 CPtrList를 대체하기 위해 만들었습니다.
    이 클래스는 MyThread 카페와 미가공 카페에서 프로그래밍
    공부를 진행하는 사람들에게 제공되는 예제에 사용됩니다.

    컨트롤을 만든 날짜 : 2021년 11월 3일
    ------------------------------------
    작성자 : 김성엽 (tipsware@naver.com)
*/

// 연결 리스트를 구성할 노드에 대한 자료형을 정의한다.
struct node {
    void *p_data;  // 노드별로 보관할 데이터 값
    node *p_prev;  // 이전 노드의 주소 (없으면 NULL)
    node *p_next;  // 다음 노드의 주소 (없으면 NULL)
};

typedef void (*DeleteFuncForTW_DoubleLL)(void *ap_data);

// 더블 링크드 리스트를 구현한 클래스
class TW_DoubleLinkedList
{
protected:
    // 연결 리스트의 시작과 끝을 기억할 포인터 변수
    node *mp_head, *mp_tail;
    // 연결 리스트에 추가된 노드의 수를 기억할 변수
    int m_node_count;
    DeleteFuncForTW_DoubleLL mp_del_func = NULL;

public:
    TW_DoubleLinkedList(DeleteFuncForTW_DoubleLL ap_del_func = NULL);   // 생성자
    ~TW_DoubleLinkedList();  // 파괴자

    // 시작 노드의 주소를 얻는 함수
    node *GetHead();
    // 마지막 노드의 주소를 얻는 함수
    node *GetTail();
    // 추가된 노드의 개수를 얻는 함수
    int Count();

    // 노드를 추가하는 함수 (메모리 할당후, 복사)
    // 예외적으로 a_data_size 값이 0이면 메모리 재할당 없이 ap_data 주소 그대로 사용
    void AddNode(void *ap_data, int a_data_size = 0);
    // 노드를 특정 노드 앞에 추가하는 함수, 동작 특성은 AddNode와 동일!
    void InsertNode(node *ap_next_node, void *ap_data, int a_data_size = 0);

    // ap_del_node에 지정된 노드를 제거한다.
    void DeleteNode(node *ap_del_node, int a_delete_flag = 1);
    // 전체 노드를 삭제하는 함수!
    void DeleteAllNode();
    // a_index 위치에 있는 노드의 주소를 반환한다. (0부터)
    node *GetNodeByIndex(int a_index);
    // a_index 위치에 있는 노드가 관리하는 데이터의 주소를 반환한다. (0부터)
    void *GetObjectByIndex(int a_index);
};

#endif
