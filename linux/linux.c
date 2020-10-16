#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/times.h>
#include <sys/vtimes.h>

#include "linux.h"

static int numProcessors;
static clock_t lastCPU, lastSysCPU, lastUserCPU;

int
parse_line(char *line)
{
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char *p = line;
    while (*p < '0' || *p > '9')
        p++;
    line[i - 3] = '\0';
    i = atoi(p);
    return i;
}

// Note: this value is in KB!
int
memory_usage(int proc_id)
{
    char str_proc_id[10];
    sprintf(str_proc_id, "%d", proc_id);

    char proc_path[80];
    strcpy(proc_path, "/proc/");
    strcat(proc_path, str_proc_id);
    strcat(proc_path, "/status");

    FILE *file = fopen(proc_path, "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL) {
        if (strncmp(line, "VmRSS:", 6) == 0) {
            result = parse_line(line);
            break;
        }
    }
    fclose(file);
    return result;
}

void
cpu_init()
{
    FILE *file;
    struct tms timeSample;
    char line[128];

    lastCPU = times(&timeSample);
    lastSysCPU = timeSample.tms_stime;
    lastUserCPU = timeSample.tms_utime;

    file = fopen("/proc/cpuinfo", "r");
    numProcessors = 0;
    while (fgets(line, 128, file) != NULL) {
        if (strncmp(line, "processor", 9) == 0)
            numProcessors++;
    }
    fclose(file);
}

double
cpu_usage()
{
    struct tms timeSample;
    clock_t now;
    double percent;

    now = times(&timeSample);
    if (now <= lastCPU || timeSample.tms_stime < lastSysCPU ||
        timeSample.tms_utime < lastUserCPU) {
        // Overflow detection. Just skip this value.
        percent = -1.0;
    } else {
        percent = (timeSample.tms_stime - lastSysCPU) +
                  (timeSample.tms_utime - lastUserCPU);
        percent /= (now - lastCPU);
        percent /= numProcessors;
        percent *= 100;
    }
    lastCPU = now;
    lastSysCPU = timeSample.tms_stime;
    lastUserCPU = timeSample.tms_utime;

    return percent;
}
