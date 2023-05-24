#include "pch.h"
#include "TW_DoubleLinkedList.h"

TW_DoubleLinkedList::TW_DoubleLinkedList(DeleteFuncForTW_DoubleLL ap_del_func)  // 생성자
{
    mp_head = mp_tail = NULL;
    m_node_count = 0;
    mp_del_func = ap_del_func;
}

TW_DoubleLinkedList::~TW_DoubleLinkedList()  // 파괴자
{
    DeleteAllNode();
}

// 시작 노드의 주소를 얻는 함수
node *TW_DoubleLinkedList::GetHead()
{
    return mp_head;
}

// 마지막 노드의 주소를 얻는 함수
node *TW_DoubleLinkedList::GetTail()
{
    return mp_tail;
}

// 추가된 노드의 개수를 얻는 함수
int TW_DoubleLinkedList::Count()
{
    return m_node_count;
}

// 노드를 추가하는 함수
void TW_DoubleLinkedList::AddNode(void *ap_data, int a_data_size)
{
    node *p_temp;
    if (mp_head != NULL) {  // 노드가 존재하는 경우!
        // 마지막 노드 위치를 p_temp에 저장한다.
        p_temp = mp_tail;
        // 마지막 노드 다음에 새로운 노드를 추가한다.
        p_temp->p_next = new node;
        // 새로 추가된 노드를 마지막 노드로 지정한다.
        mp_tail = p_temp->p_next;
    } else {  // 노드가 없는 경우 (첫 노드인 경우)
        // 첫 노드를 생성한다.
        mp_head = new node;
        // 첫 노드는 마지막 노드이기도 하다.
        mp_tail = mp_head;
        // 첫 노드는 이전 노드가 없다.
        p_temp = NULL;
    }

    if (a_data_size) {
        // 현재 노드에 값을 저장하기 위해 전달된 데이터의 크기만큼 메모리 할당
        mp_tail->p_data = new UINT8[a_data_size];
        // 할당된 메모리에 전달된 데이터 복사
        memcpy(mp_tail->p_data, ap_data, a_data_size);
    } else mp_tail->p_data = ap_data;  // 메모리 추가 할당 없이 주소 그대로 사용

    // 다음 노드가 없음을 설정한다.
    mp_tail->p_next = NULL;
    // 현재 노드에 이전 노드의 주소를 대입한다.
    mp_tail->p_prev = p_temp;
    // 추가된 노드의 수를 증가시킨다.
    m_node_count++;
}

// 노드를 특정 노드 앞에 추가하는 함수
void TW_DoubleLinkedList::InsertNode(node *ap_next_node, void *ap_data, int a_data_size)
{
    // 연결 리스트의 마지막 위치에 노드를 추가한다.
    if (mp_head == NULL || ap_next_node == NULL) AddNode(ap_data, a_data_size);
    else {
        node *p_temp = new node;
        // 기존 노드를 다음 노드로 설정한다.
        p_temp->p_next = ap_next_node;
        // 기존 노드의 이전 노드를 새 노드의 이전 노드로 설정한다.
        p_temp->p_prev = ap_next_node->p_prev;
        // 새 노드의 이전 노드가 있다면 해당 노드의 다음 노드로 새 노드를 설정한다.
        if (p_temp->p_prev != NULL) p_temp->p_prev->p_next = p_temp;
        else mp_head = p_temp;  // 이전 노드가 없다는 자신이 헤더 노드가 된다.
        // 기존 노드의 이전 노드로 새 노드를 설정한다.
        ap_next_node->p_prev = p_temp;

        if (a_data_size) {
            // 현재 노드에 값을 저장하기 위해 전달된 데이터의 크기만큼 메모리 할당
            p_temp->p_data = new UINT8[a_data_size];
            // 할당된 메모리에 전달된 데이터 복사
            memcpy(p_temp->p_data, ap_data, a_data_size);
        } else p_temp->p_data = ap_data;  // 메모리 추가 할당 없이 주소 그대로 사용

        // 추가된 노드의 수를 증가시킨다.
        m_node_count++;
    }
}

// ap_del_node에 지정된 노드를 제거한다.
void TW_DoubleLinkedList::DeleteNode(node *ap_del_node, int a_delete_flag)
{
    if (ap_del_node == mp_head) {  // 삭제할 노드가 시작 노드인 경우
        mp_head = mp_head->p_next;  // 헤더를 다음 노드로 이동
        // 다음 노드가 있다면 다음 노드가 시작 노드이기 때문에 이전 노드가
        // 없다는 뜻으로 p_prev 값에 NULL을 대입한다. 만약 헤더 노드가 NULL
        // 이라면 노드가 한 개만 있었다는 뜻이기 때문에 테일 노드도 NULL로 변경한다.
        if (mp_head) mp_head->p_prev = NULL;
        else mp_tail = NULL;
    }
    else if (ap_del_node == mp_tail) {  // 삭제할 노드가 끝 노드인 경우
    // 테일을 이전 노드로 이동한다.
        mp_tail = mp_tail->p_prev;
        // 마지막 노드로 설정된 노드는 다음 노드가 없다.
        mp_tail->p_next = NULL;
    } else {  // 삭제할 노드가 중간 노드인 경우!
    // A <-> B <-> C 에서 B가 삭제되는 경우
    // B의 다음 노드인 C의 주소를 A노드의 p_next에 대입하고
        ap_del_node->p_prev->p_next = ap_del_node->p_next;
        // B의 이전 노드인 A의 주소를 C노드의 p_prev에 대입한다.
        ap_del_node->p_next->p_prev = ap_del_node->p_prev;
    }

    if (a_delete_flag) {
        // 사용자가 지정한 삭제 함수가 있다면 삭제 함수를 호출해준다.
        if (mp_del_func) (*mp_del_func)(ap_del_node->p_data);
        else {
            // 노드가 가리키는 메모리를 해제한다.
            delete[](UINT8 *)ap_del_node->p_data;
        }
    }
    // ap_del_node를 해제한다.
    delete ap_del_node;
    // 추가된 노드의 수를 감소시킨다.
    m_node_count--;
}

// 전체 노드를 삭제하는 함수!
void TW_DoubleLinkedList::DeleteAllNode()
{
    if (mp_head) {  // 노드가 존재하는지 체크!
        node *p = mp_head->p_next;  // 두 번째 노드로 이동한다.
        while (p) {  // 노드가 존재하는지 체크!
            // 사용자가 지정한 삭제 함수가 있다면 삭제 함수를 호출하고
            // 없으면 노드가 가리키는 메모리를 직접 해제한다.
            if (mp_del_func) (*mp_del_func)(p->p_prev->p_data);
            else delete[](UINT8 *)p->p_prev->p_data;

            delete p->p_prev;  // 이전 노드를 삭제한다.
            p = p->p_next;  // 다음 노드로 이동한다.
        }
        // 사용자가 지정한 삭제 함수가 있다면 삭제 함수를 호출하고
        // 없으면 노드가 가리키는 메모리를 직접 해제한다.
        if (mp_del_func) (*mp_del_func)(mp_tail->p_data);
        else delete[](UINT8 *)mp_tail->p_data;

        delete mp_tail; // 마지막 노드를 삭제한다.
        mp_head = mp_tail = NULL;  // 노드의 시작과 끝 정보를 초기화한다.
        m_node_count = 0;  // 추가된 노드의 수를 0으로 초기화한다.
    }
}

// a_index 위치에 있는 노드의 주소를 반환한다. (0부터)
node *TW_DoubleLinkedList::GetNodeByIndex(int a_index)
{
    if (m_node_count && a_index < m_node_count) {
        node *p = mp_head;  // 첫 번째 노드로 이동한다.
        // a_index 위치에 있는 노드로 이동한다.
        for (int i = 0; i < a_index; i++) p = p->p_next;
        // a_index 위치에 있는 노드의 주소를 반환한다.
        return p;
    }
    return NULL;  // a_index가 잘못됨
}

// a_index 위치에 있는 노드가 관리하는 데이터의 주소를 반환한다. (0부터)
void *TW_DoubleLinkedList::GetObjectByIndex(int a_index)
{
    // a_index 위치에 있는 노드의 주소를 찾는다.
    node *p_node = GetNodeByIndex(a_index);
    // 해당 위치에 노드가 존재한다면 노드에 저장된 데이터의 주소를 반환한다.
    if (p_node != NULL) return p_node->p_data;
    return NULL;  // 노드가 존재하지 않는 경우!
}

