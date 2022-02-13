#include "pch.h"
#include "WorkView.h"


// TWD_View�� ��ӹ��� WorkViewŬ����

WorkView::WorkView()
{
    // �⺻ �۲��� ����� ������ �����Ѵ�.
    m_def_color = ColorF(0.3f, 0.8f, 1.0f, 1.0f);
    // �⺻ �۲��� �̸��� ũ�⸦ �����Ѵ�.
    memcpy(m_def_font_name, _T("����ǹ��� �־�"), 18);
    m_def_font_size = 22.0f;
}

// �� ��ư�� ��ǥ�� ���� �� ����ϴ� �Լ�
D2D1_RECT_F* WorkView::GetBtnRect(int a_index)
{
    return m_btn_rect + a_index;
}

// ��ư ���¸� �����ϴ� �Լ�
void WorkView::SetBtnState(int a_index, unsigned char a_state)
{
    m_btn_state[a_index] = a_state;
}

// ��ư ���¸� ��� �Լ�
unsigned char WorkView::GetBtnState(int a_index)
{
    return m_btn_state[a_index];
}

// ���� ��ư�� �ε����� �����ϴ� �Լ�
void WorkView::SetSelectedBtn(unsigned char a_btn_index)
{
    m_selected_btn = a_btn_index;
}

// ���� ��ư�� �ε����� ��� �Լ�
unsigned char WorkView::GetSelectedBtn()
{
    return m_selected_btn;
}

// View �׸��⸦ �۾��� �Լ�
void WorkView::OnDraw()
{
    // ȭ���� ���������� ä���.
    mp_target->Clear(m_bk_color);
    if (mp_text_format) {
        // ��ư�� ���
        mp_user_brush->SetColor(m_btn_border_color[m_btn_state[0]]);
        mp_target->DrawRectangle(m_btn_rect[0], mp_user_brush, 3);
        mp_user_brush->SetColor(m_text_color[m_btn_state[0]]);
        D2D1_RECT_F r = m_btn_rect[0];
        if (m_btn_state[0]) {           // ��ư�� ������ ��¦ �Ʒ��� �̵�
            r.left += 1.0f;
            r.top += 1.0f;
            r.right += 1.0f;
            r.bottom += 1.0f;
        }
        mp_target->DrawText(_T("�ռ���"), 3, mp_text_format, r, mp_user_brush);

        // �Ǵٸ� ��ư�� ����Ѵ�.
        D2D1_ROUNDED_RECT round_r = { m_btn_rect[1], 9.0f, 9.0f };
        mp_user_brush->SetColor(m_btn_border_color[m_btn_state[1]]);
        mp_target->DrawRoundedRectangle(&round_r, mp_user_brush, 3);
        mp_user_brush->SetColor(m_text_color[m_btn_state[1]]);
        r = m_btn_rect[1];
        if (m_btn_state[1]) {               // ��ư�� ������ ��¦ �Ʒ��� �̵�
            r.left += 1.0f;
            r.top += 1.0f;
            r.right += 1.0f;
            r.bottom += 1.0f;
        }
        mp_target->DrawText(_T("�̰���"), 3, mp_text_format, r, mp_user_brush);
        
        // ������ ��ư ���
        round_r.rect = m_btn_rect[2];
        round_r.radiusX = 20.0f;
        round_r.radiusY = 20.0f;
        mp_user_brush->SetColor(m_btn_border_color[m_btn_state[2]]);
        mp_target->DrawRoundedRectangle(&round_r, mp_user_brush, 3);
        mp_user_brush->SetColor(m_text_color[m_btn_state[2]]);
        r = m_btn_rect[2];
        if (m_btn_state[2]) {               // ��ư�� ������ ��¦ �Ʒ��� �̵�
            r.left += 1.0f;
            r.top += 1.0f;
            r.right += 1.0f;
            r.bottom += 1.0f;
        }
        mp_target->DrawText(_T("�ױ�����"), 4, mp_text_format, r, mp_user_brush);
    }
}
