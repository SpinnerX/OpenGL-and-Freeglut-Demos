///////////////////////////////////////////////////////////////////////////////
// procedure.h
// ===========
// Window procedure and dialog procedure callback functions.
// Windows will call this function whenever a event is triggered. It routes
// the message to the controller associated with window handle.
//
// LRESULT type is __int64 in _WIN64 and long (32bit) in _WIN32.
// INT_PTR type is __int64 in _WIN64 and int (32bit) in _WIN32.
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2006-06-24
// UPDATED: 2022-12-19
///////////////////////////////////////////////////////////////////////////////

#ifndef WIN_PROCEDURE_H
#define WIN_PROCEDURE_H

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400                     // for WM_MOUUSEWHEEL. Is this right?
#endif

#include <windows.h>

namespace Win
{
    // window procedure router
    LRESULT CALLBACK windowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    // dialog procedure router
    INT_PTR CALLBACK dialogProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
}

#endif
