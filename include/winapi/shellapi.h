#ifndef SHELLAPI_H
#define SHELLAPI_H

#include <winnt.h>

DECLARE_HANDLE(HDROP);

UINT DragQueryFileA(HDROP hDrop, UINT iFile, LPSTR lpszFile, UINT cch);
UINT DragQueryFileW(HDROP hDrop, UINT iFile, LPWSTR lpszFile, UINT cch);
void DragFinish(HDROP hDrop);
void DragAcceptFiles(HWND hWnd, BOOL fAccept);

LPWSTR* CommandLineToArgvW(LPCWSTR lpCmdLine, int* pNumArgs);

#endif // SHELLAPI_H
