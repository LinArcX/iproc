#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include "../windows/windows.h"
#elif __linux__
#include <unistd.h>

#include "../linux/linux.h"
#endif

void
show_usage(char *name)
{
    fprintf(stdout,
            "Usage: %s\n"
            "Options:\n"
            "\t-p,--processID \tSpecify the processID to watch\n"
            "\t-i,--interval \tSpecify interval\n"
            "\t-h,--help \tShow this help message\n",
            name);
}

int
main(int argc, char **argv)
{
    // At least pass -p, please!
    if (argc < 2) {
        show_usage(argv[0]);
        return 1;
    }

    int pid = 0;
    int interval = 0;
    int elapsed = 0;

    for (int i = 1; i < argc; ++i) {
        char *arg = argv[i];
        if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0) {
            show_usage(argv[0]);
            return 0;
        } else if (strcmp(arg, "-p") == 0 || strcmp(arg, "--processID") == 0) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                pid = atoi(argv[++i]);
            } else { // Uh-oh, there was no argument to the destination option.
                fprintf(stderr, "--processID option requires one argument.");
                return 1;
            }
        } else if (strcmp(arg, "-i") == 0 || strcmp(arg, "--interval") == 0) {
            if (i + 1 < argc) {
                interval = atoi(argv[++i]);
            } else {
                fprintf(stderr, "--interval option requires one argument.");
                return 1;
            }
        }
    }

    if (pid) {
        if (interval) {
            for (;;) {
#ifdef WIN32
                elapsed += interval;
                Sleep(interval * 1000);

                printf("[%d]\n\tMem: %d Kb\n", elapsed, memory_usage(pid));
                printf("\tCpu: %d%%\n", cpu_usage(pid));
#elif __linux__
                sleep(g_interval);
                printf("Mem: %d Kb\n", memory_usage(g_pid));

                cpu_init();
                printf("Cpu: %f\n", cpu_usage());
#endif
            }
        } else {
            for (;;) {
#ifdef WIN32
                elapsed += 2;
                Sleep(2000);

                printf("[%d]\n\tMem: %d Kb\n", elapsed, memory_usage(pid));
                printf("\tCpu: %d%%\n", cpu_usage(pid));
#elif __linux__
                sleep(2);
                printf("Mem: %d Kb\n", memory_usage(g_pid));

                cpu_init();
                printf("Cpu: %f\n", cpu_usage());
#endif
            }
        }
    }
    return 0;
}
