#ifndef _TW_DOUBLE_LINKED_LIST_H_
#define _TW_DOUBLE_LINKED_LIST_H_

/*
    �� Ŭ������ ���� ��ũ�� ����Ʈ�� ������ ���Դϴ�.
    MFC�� CPtrList�� ��ü�ϱ� ���� ��������ϴ�.
    �� Ŭ������ MyThread ī��� �̰��� ī�信�� ���α׷���
    ���θ� �����ϴ� ����鿡�� �����Ǵ� ������ ���˴ϴ�.

    ��Ʈ���� ���� ��¥ : 2021�� 11�� 3��
    ------------------------------------
    �ۼ��� : �輺�� (tipsware@naver.com)
*/

// ���� ����Ʈ�� ������ ��忡 ���� �ڷ����� �����Ѵ�.
struct node {
    void *p_data;  // ��庰�� ������ ������ ��
    node *p_prev;  // ���� ����� �ּ� (������ NULL)
    node *p_next;  // ���� ����� �ּ� (������ NULL)
};

typedef void (*DeleteFuncForTW_DoubleLL)(void *ap_data);

// ���� ��ũ�� ����Ʈ�� ������ Ŭ����
class TW_DoubleLinkedList
{
protected:
    // ���� ����Ʈ�� ���۰� ���� ����� ������ ����
    node *mp_head, *mp_tail;
    // ���� ����Ʈ�� �߰��� ����� ���� ����� ����
    int m_node_count;
    DeleteFuncForTW_DoubleLL mp_del_func = NULL;

public:
    TW_DoubleLinkedList(DeleteFuncForTW_DoubleLL ap_del_func = NULL);   // ������
    ~TW_DoubleLinkedList();  // �ı���

    // ���� ����� �ּҸ� ��� �Լ�
    node *GetHead();
    // ������ ����� �ּҸ� ��� �Լ�
    node *GetTail();
    // �߰��� ����� ������ ��� �Լ�
    int Count();

    // ��带 �߰��ϴ� �Լ� (�޸� �Ҵ���, ����)
    // ���������� a_data_size ���� 0�̸� �޸� ���Ҵ� ���� ap_data �ּ� �״�� ���
    void AddNode(void *ap_data, int a_data_size = 0);
    // ��带 Ư�� ��� �տ� �߰��ϴ� �Լ�, ���� Ư���� AddNode�� ����!
    void InsertNode(node *ap_next_node, void *ap_data, int a_data_size = 0);

    // ap_del_node�� ������ ��带 �����Ѵ�.
    void DeleteNode(node *ap_del_node, int a_delete_flag = 1);
    // ��ü ��带 �����ϴ� �Լ�!
    void DeleteAllNode();
    // a_index ��ġ�� �ִ� ����� �ּҸ� ��ȯ�Ѵ�. (0����)
    node *GetNodeByIndex(int a_index);
    // a_index ��ġ�� �ִ� ��尡 �����ϴ� �������� �ּҸ� ��ȯ�Ѵ�. (0����)
    void *GetObjectByIndex(int a_index);
};

#endif
