#include "pch.h"
#include "TW_DoubleLinkedList.h"

TW_DoubleLinkedList::TW_DoubleLinkedList(DeleteFuncForTW_DoubleLL ap_del_func)  // ������
{
    mp_head = mp_tail = NULL;
    m_node_count = 0;
    mp_del_func = ap_del_func;
}

TW_DoubleLinkedList::~TW_DoubleLinkedList()  // �ı���
{
    DeleteAllNode();
}

// ���� ����� �ּҸ� ��� �Լ�
node *TW_DoubleLinkedList::GetHead()
{
    return mp_head;
}

// ������ ����� �ּҸ� ��� �Լ�
node *TW_DoubleLinkedList::GetTail()
{
    return mp_tail;
}

// �߰��� ����� ������ ��� �Լ�
int TW_DoubleLinkedList::Count()
{
    return m_node_count;
}

// ��带 �߰��ϴ� �Լ�
void TW_DoubleLinkedList::AddNode(void *ap_data, int a_data_size)
{
    node *p_temp;
    if (mp_head != NULL) {  // ��尡 �����ϴ� ���!
        // ������ ��� ��ġ�� p_temp�� �����Ѵ�.
        p_temp = mp_tail;
        // ������ ��� ������ ���ο� ��带 �߰��Ѵ�.
        p_temp->p_next = new node;
        // ���� �߰��� ��带 ������ ���� �����Ѵ�.
        mp_tail = p_temp->p_next;
    } else {  // ��尡 ���� ��� (ù ����� ���)
        // ù ��带 �����Ѵ�.
        mp_head = new node;
        // ù ���� ������ ����̱⵵ �ϴ�.
        mp_tail = mp_head;
        // ù ���� ���� ��尡 ����.
        p_temp = NULL;
    }

    if (a_data_size) {
        // ���� ��忡 ���� �����ϱ� ���� ���޵� �������� ũ�⸸ŭ �޸� �Ҵ�
        mp_tail->p_data = new UINT8[a_data_size];
        // �Ҵ�� �޸𸮿� ���޵� ������ ����
        memcpy(mp_tail->p_data, ap_data, a_data_size);
    } else mp_tail->p_data = ap_data;  // �޸� �߰� �Ҵ� ���� �ּ� �״�� ���

    // ���� ��尡 ������ �����Ѵ�.
    mp_tail->p_next = NULL;
    // ���� ��忡 ���� ����� �ּҸ� �����Ѵ�.
    mp_tail->p_prev = p_temp;
    // �߰��� ����� ���� ������Ų��.
    m_node_count++;
}

// ��带 Ư�� ��� �տ� �߰��ϴ� �Լ�
void TW_DoubleLinkedList::InsertNode(node *ap_next_node, void *ap_data, int a_data_size)
{
    // ���� ����Ʈ�� ������ ��ġ�� ��带 �߰��Ѵ�.
    if (mp_head == NULL || ap_next_node == NULL) AddNode(ap_data, a_data_size);
    else {
        node *p_temp = new node;
        // ���� ��带 ���� ���� �����Ѵ�.
        p_temp->p_next = ap_next_node;
        // ���� ����� ���� ��带 �� ����� ���� ���� �����Ѵ�.
        p_temp->p_prev = ap_next_node->p_prev;
        // �� ����� ���� ��尡 �ִٸ� �ش� ����� ���� ���� �� ��带 �����Ѵ�.
        if (p_temp->p_prev != NULL) p_temp->p_prev->p_next = p_temp;
        else mp_head = p_temp;  // ���� ��尡 ���ٴ� �ڽ��� ��� ��尡 �ȴ�.
        // ���� ����� ���� ���� �� ��带 �����Ѵ�.
        ap_next_node->p_prev = p_temp;

        if (a_data_size) {
            // ���� ��忡 ���� �����ϱ� ���� ���޵� �������� ũ�⸸ŭ �޸� �Ҵ�
            p_temp->p_data = new UINT8[a_data_size];
            // �Ҵ�� �޸𸮿� ���޵� ������ ����
            memcpy(p_temp->p_data, ap_data, a_data_size);
        } else p_temp->p_data = ap_data;  // �޸� �߰� �Ҵ� ���� �ּ� �״�� ���

        // �߰��� ����� ���� ������Ų��.
        m_node_count++;
    }
}

// ap_del_node�� ������ ��带 �����Ѵ�.
void TW_DoubleLinkedList::DeleteNode(node *ap_del_node, int a_delete_flag)
{
    if (ap_del_node == mp_head) {  // ������ ��尡 ���� ����� ���
        mp_head = mp_head->p_next;  // ����� ���� ���� �̵�
        // ���� ��尡 �ִٸ� ���� ��尡 ���� ����̱� ������ ���� ��尡
        // ���ٴ� ������ p_prev ���� NULL�� �����Ѵ�. ���� ��� ��尡 NULL
        // �̶�� ��尡 �� ���� �־��ٴ� ���̱� ������ ���� ��嵵 NULL�� �����Ѵ�.
        if (mp_head) mp_head->p_prev = NULL;
        else mp_tail = NULL;
    }
    else if (ap_del_node == mp_tail) {  // ������ ��尡 �� ����� ���
    // ������ ���� ���� �̵��Ѵ�.
        mp_tail = mp_tail->p_prev;
        // ������ ���� ������ ���� ���� ��尡 ����.
        mp_tail->p_next = NULL;
    } else {  // ������ ��尡 �߰� ����� ���!
    // A <-> B <-> C ���� B�� �����Ǵ� ���
    // B�� ���� ����� C�� �ּҸ� A����� p_next�� �����ϰ�
        ap_del_node->p_prev->p_next = ap_del_node->p_next;
        // B�� ���� ����� A�� �ּҸ� C����� p_prev�� �����Ѵ�.
        ap_del_node->p_next->p_prev = ap_del_node->p_prev;
    }

    if (a_delete_flag) {
        // ����ڰ� ������ ���� �Լ��� �ִٸ� ���� �Լ��� ȣ�����ش�.
        if (mp_del_func) (*mp_del_func)(ap_del_node->p_data);
        else {
            // ��尡 ����Ű�� �޸𸮸� �����Ѵ�.
            delete[](UINT8 *)ap_del_node->p_data;
        }
    }
    // ap_del_node�� �����Ѵ�.
    delete ap_del_node;
    // �߰��� ����� ���� ���ҽ�Ų��.
    m_node_count--;
}

// ��ü ��带 �����ϴ� �Լ�!
void TW_DoubleLinkedList::DeleteAllNode()
{
    if (mp_head) {  // ��尡 �����ϴ��� üũ!
        node *p = mp_head->p_next;  // �� ��° ���� �̵��Ѵ�.
        while (p) {  // ��尡 �����ϴ��� üũ!
            // ����ڰ� ������ ���� �Լ��� �ִٸ� ���� �Լ��� ȣ���ϰ�
            // ������ ��尡 ����Ű�� �޸𸮸� ���� �����Ѵ�.
            if (mp_del_func) (*mp_del_func)(p->p_prev->p_data);
            else delete[](UINT8 *)p->p_prev->p_data;

            delete p->p_prev;  // ���� ��带 �����Ѵ�.
            p = p->p_next;  // ���� ���� �̵��Ѵ�.
        }
        // ����ڰ� ������ ���� �Լ��� �ִٸ� ���� �Լ��� ȣ���ϰ�
        // ������ ��尡 ����Ű�� �޸𸮸� ���� �����Ѵ�.
        if (mp_del_func) (*mp_del_func)(mp_tail->p_data);
        else delete[](UINT8 *)mp_tail->p_data;

        delete mp_tail; // ������ ��带 �����Ѵ�.
        mp_head = mp_tail = NULL;  // ����� ���۰� �� ������ �ʱ�ȭ�Ѵ�.
        m_node_count = 0;  // �߰��� ����� ���� 0���� �ʱ�ȭ�Ѵ�.
    }
}

// a_index ��ġ�� �ִ� ����� �ּҸ� ��ȯ�Ѵ�. (0����)
node *TW_DoubleLinkedList::GetNodeByIndex(int a_index)
{
    if (m_node_count && a_index < m_node_count) {
        node *p = mp_head;  // ù ��° ���� �̵��Ѵ�.
        // a_index ��ġ�� �ִ� ���� �̵��Ѵ�.
        for (int i = 0; i < a_index; i++) p = p->p_next;
        // a_index ��ġ�� �ִ� ����� �ּҸ� ��ȯ�Ѵ�.
        return p;
    }
    return NULL;  // a_index�� �߸���
}

// a_index ��ġ�� �ִ� ��尡 �����ϴ� �������� �ּҸ� ��ȯ�Ѵ�. (0����)
void *TW_DoubleLinkedList::GetObjectByIndex(int a_index)
{
    // a_index ��ġ�� �ִ� ����� �ּҸ� ã�´�.
    node *p_node = GetNodeByIndex(a_index);
    // �ش� ��ġ�� ��尡 �����Ѵٸ� ��忡 ����� �������� �ּҸ� ��ȯ�Ѵ�.
    if (p_node != NULL) return p_node->p_data;
    return NULL;  // ��尡 �������� �ʴ� ���!
}

