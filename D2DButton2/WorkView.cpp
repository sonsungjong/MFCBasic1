#include "pch.h"
#include "WorkView.h"


// TWD_View를 상속받은 WorkView클래스

WorkView::WorkView()
{
    // 기본 글꼴의 색상과 선색을 지정한다.
    m_def_color = ColorF(0.3f, 0.8f, 1.0f, 1.0f);
    // 기본 글꼴의 이름과 크기를 지정한다.
    memcpy(m_def_font_name, _T("배달의민족 주아"), 18);
    m_def_font_size = 22.0f;
}

// 각 버튼의 좌표를 얻을 때 사용하는 함수
D2D1_RECT_F* WorkView::GetBtnRect(int a_index)
{
    return m_btn_rect + a_index;
}

// 버튼 상태를 설정하는 함수
void WorkView::SetBtnState(int a_index, unsigned char a_state)
{
    m_btn_state[a_index] = a_state;
}

// 버튼 상태를 얻는 함수
unsigned char WorkView::GetBtnState(int a_index)
{
    return m_btn_state[a_index];
}

// 선택 버튼의 인덱스를 설정하는 함수
void WorkView::SetSelectedBtn(unsigned char a_btn_index)
{
    m_selected_btn = a_btn_index;
}

// 선택 버튼의 인덱스를 얻는 함수
unsigned char WorkView::GetSelectedBtn()
{
    return m_selected_btn;
}

// View 그리기를 작업할 함수
void WorkView::OnDraw()
{
    // 화면을 검은색으로 채운다.
    mp_target->Clear(m_bk_color);
    if (mp_text_format) {
        // 버튼을 출력
        mp_user_brush->SetColor(m_btn_border_color[m_btn_state[0]]);
        mp_target->DrawRectangle(m_btn_rect[0], mp_user_brush, 3);
        mp_user_brush->SetColor(m_text_color[m_btn_state[0]]);
        D2D1_RECT_F r = m_btn_rect[0];
        if (m_btn_state[0]) {           // 버튼이 눌리면 살짝 아래로 이동
            r.left += 1.0f;
            r.top += 1.0f;
            r.right += 1.0f;
            r.bottom += 1.0f;
        }
        mp_target->DrawText(_T("손성종"), 3, mp_text_format, r, mp_user_brush);

        // 또다른 버튼을 출력한다.
        D2D1_ROUNDED_RECT round_r = { m_btn_rect[1], 9.0f, 9.0f };
        mp_user_brush->SetColor(m_btn_border_color[m_btn_state[1]]);
        mp_target->DrawRoundedRectangle(&round_r, mp_user_brush, 3);
        mp_user_brush->SetColor(m_text_color[m_btn_state[1]]);
        r = m_btn_rect[1];
        if (m_btn_state[1]) {               // 버튼이 눌리면 살짝 아래로 이동
            r.left += 1.0f;
            r.top += 1.0f;
            r.right += 1.0f;
            r.bottom += 1.0f;
        }
        mp_target->DrawText(_T("미가공"), 3, mp_text_format, r, mp_user_brush);
        
        // 마지막 버튼 출력
        round_r.rect = m_btn_rect[2];
        round_r.radiusX = 20.0f;
        round_r.radiusY = 20.0f;
        mp_user_brush->SetColor(m_btn_border_color[m_btn_state[2]]);
        mp_target->DrawRoundedRectangle(&round_r, mp_user_brush, 3);
        mp_user_brush->SetColor(m_text_color[m_btn_state[2]]);
        r = m_btn_rect[2];
        if (m_btn_state[2]) {               // 버튼이 눌리면 살짝 아래로 이동
            r.left += 1.0f;
            r.top += 1.0f;
            r.right += 1.0f;
            r.bottom += 1.0f;
        }
        mp_target->DrawText(_T("네글자임"), 4, mp_text_format, r, mp_user_brush);
    }
}
