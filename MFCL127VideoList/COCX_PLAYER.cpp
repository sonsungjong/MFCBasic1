// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated
// by Microsoft Visual C++, your modifications will be overwritten.

#include "pch.h"
#include "COCX_PLAYER.h"

/////////////////////////////////////////////////////////////////////////////
// COCX_PLAYER

IMPLEMENT_DYNCREATE(COCX_PLAYER, CWnd)

/////////////////////////////////////////////////////////////////////////////
// COCX_PLAYER Properties

/////////////////////////////////////////////////////////////////////////////
// COCX_PLAYER Operations

void COCX_PLAYER::SetUrl(LPCTSTR lpszNewValue)
{
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, lpszNewValue);
}
