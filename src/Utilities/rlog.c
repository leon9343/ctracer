#include "rlog.h"

#include <stdio.h>
#include <stdarg.h>

#define COLOR_RESET  "\033[0m"
#define COLOR_BLUE   "\033[34m"
#define COLOR_ORANGE "\033[33m"
#define COLOR_RED    "\033[31m"

void rlog(LogLevel level, const char* m, ...) {
  switch (level) {
    case INFO:
      printf("%s[INFO]: ", COLOR_BLUE);
      break;
    case WARNING:
      printf("%s[WARNING]: ", COLOR_ORANGE);
      break;
    case ERROR:
      printf("%s[ERROR]: ", COLOR_RED);
      break;
  }

  va_list args;
  va_start(args, m);
  vprintf(m, args);
  va_end(args);

  printf("%s\n", COLOR_RESET);
}
