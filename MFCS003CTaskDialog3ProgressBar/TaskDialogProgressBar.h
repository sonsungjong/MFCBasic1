#ifndef TASK_DIALOG_PROGRESS_BAR_H_
#define TASK_DIALOG_PROGRESS_BAR_H_

#include <afxtaskdialog.h>
#include <Windows.h>
#include <atomic>

class TaskDialogProgressBar : public CTaskDialog
{
public:
	TaskDialogProgressBar();
protected:
	virtual HRESULT OnCommandControlClick(_In_ int nCommandControlID);
	virtual HRESULT OnTimer(long a_time);

private:
	int m_step = 0;
	std::atomic_int m_is_paused = 0;
};

#endif			TASK_DIALOG_PROGRESS_BAR_H_