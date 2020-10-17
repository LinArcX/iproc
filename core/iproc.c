#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include "../windows/windows.h"
#elif __linux__
#include <unistd.h>

#include "../linux/linux.h"
#endif

void show_usage(char *name) {
  fprintf(stdout,
          "Usage: %s\n"
          "Options:\n"
          "\t-p,--process-id \tThe process-id to watch\n"
          "\t-i,--interval \tThe period of time to do unlimited "
          "calculations.(default = 2)\n"
          "\t-o,--one-shot \tJust calculate once\n"
          "\t-r,--repetition \tThe number of repetitions\n"
          "\t-h,--help \tShow this help message\n",
          name);
}

int main(int argc, char **argv) {
  // -p is necessary!
  if (argc < 2) {
    show_usage(argv[0]);
    return 1;
  }

  int pid = 0;
  int elapsed = 0;

  int interval = 0;
  int one_shot = 0;
  int repetition = 0;

  for (int i = 1; i < argc; ++i) {
    char *arg = argv[i];
    if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0) {
      show_usage(argv[0]);
      return 0;
    } else if (strcmp(arg, "-p") == 0 || strcmp(arg, "--process-id") == 0) {
      if (i + 1 < argc) {  // Make sure we aren't at the end of argv!
        pid = atoi(argv[++i]);
      } else {  // Uh-oh, there was no argument to the destination option.
        fprintf(stderr, "--process-id option requires one argument.");
        return 1;
      }
    } else if (strcmp(arg, "-i") == 0 || strcmp(arg, "--interval") == 0) {
      if (i + 1 < argc) {
        interval = atoi(argv[++i]);
      } else {
        fprintf(stderr, "--interval option requires one argument.");
        return 1;
      }
    } else if (strcmp(arg, "-o") == 0 || strcmp(arg, "--one-shot") == 0) {
      one_shot = 1;
    } else if (strcmp(arg, "-r") == 0 || strcmp(arg, "--repetition") == 0) {
      if (i + 1 < argc) {
        repetition = atoi(argv[++i]);
      } else {
        fprintf(stderr, "--repetition option requires one argument.");
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
        elapsed += interval;
        sleep(interval);

        cpu_init();
        printf("[%d]\n\tMem: %d Kb\n", elapsed, memory_usage(pid));
        printf("\tCpu: %f%%\n", cpu_usage());
#endif
      }
    } else if (one_shot) {
#ifdef WIN32
      printf("[%d]\n\tMem: %d Kb\n", elapsed, memory_usage(pid));
      printf("\tCpu: %d%%\n", cpu_usage(pid));
      // system("ps -o\"% C\" -p 30747");
#elif __linux__
      cpu_init();
      printf("[%d]\n\tMem: %d Kb\n", elapsed, memory_usage(pid));
      printf("\tCpu: %f%%\n", cpu_usage());
#endif
    } else if (repetition) {
      for (int i = 0; i < repetition; i++) {
#ifdef WIN32
        elapsed += 2;
        Sleep(2000);

        printf("[%d]\n\tMem: %d Kb\n", elapsed, memory_usage(pid));
        printf("\tCpu: %d%%\n", cpu_usage(pid));
#elif __linux__
        elapsed += 2;
        sleep(2);

        cpu_init();
        printf("[%d]\n\tMem: %d Kb\n", elapsed, memory_usage(pid));
        printf("\tCpu: %f%%\n", cpu_usage());
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
        elapsed += 2;
        sleep(2);

        cpu_init();
        printf("[%d]\n\tMem: %d Kb\n", elapsed, memory_usage(pid));
        printf("\tCpu: %f%%\n", cpu_usage());
#endif
      }
    }
  }
  return 0;
}
