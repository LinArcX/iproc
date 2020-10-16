#ifndef _IPROC_WINDOWS_H
#define _IPROC_WINDOWS_H

#include <Windows.h>

SIZE_T memory_usage(DWORD proc_id);
int cpu_usage(int proc_id);
#endif  // _IPROC_WINDOWS_H
