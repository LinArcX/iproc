#include "windows.h"
//
#include <Pdh.h>
#include <Psapi.h>

SIZE_T
memory_usage(DWORD process - id)
{
    HANDLE hProcess;
    SIZE_T mem_usage = 0;
    PROCESS_MEMORY_COUNTERS_EX pmc;

    hProcess = OpenProcess(
      PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, process - id);

    if (NULL == hProcess) {
        return;
    }

    if (GetProcessMemoryInfo(
          hProcess, (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc))) {
        mem_usage = pmc.WorkingSetSize / 1024;
    }

    CloseHandle(hProcess);
    return mem_usage;
}

typedef long long int64_t;
typedef unsigned long long uint64_t;

static uint64_t
file_time_2_utc(const FILETIME *ftime)
{
    LARGE_INTEGER li;
    li.LowPart = ftime->dwLowDateTime;
    li.HighPart = ftime->dwHighDateTime;
    return li.QuadPart;
}

static int
get_processor_number()
{
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    return (int)info.dwNumberOfProcessors;
}

int
cpu_usage(int pid)
{
    static int processor_count_ = -1;
    static int64_t last_time_ = 0;
    static int64_t last_system_time_ = 0;

    FILETIME now;
    FILETIME creation_time;
    FILETIME exit_time;
    FILETIME kernel_time;
    FILETIME user_time;
    int64_t system_time;
    int64_t time;
    int64_t system_time_delta;
    int64_t time_delta;

    int cpu = -1;

    if (processor_count_ == -1) {
        processor_count_ = get_processor_number();
    }

    GetSystemTimeAsFileTime(&now);

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!GetProcessTimes(
          hProcess, &creation_time, &exit_time, &kernel_time, &user_time)) {
        // can not find the process
        exit(EXIT_FAILURE);
    }
    system_time =
      (file_time_2_utc(&kernel_time) + file_time_2_utc(&user_time)) /
      processor_count_;
    time = file_time_2_utc(&now);

    if ((last_system_time_ == 0) || (last_time_ == 0)) {
        last_system_time_ = system_time;
        last_time_ = time;
        return cpu_usage(pid);
    }

    system_time_delta = system_time - last_system_time_;
    time_delta = time - last_time_;

    if (time_delta == 0) {
        return cpu_usage(pid);
    }

    cpu = (int)((system_time_delta * 100 + time_delta / 2) / time_delta);
    last_system_time_ = system_time;
    last_time_ = time;
    return cpu;
    return 0;
}
