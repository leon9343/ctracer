#pragma once

typedef enum {
  INFO,
  WARNING,
  ERROR
} LogLevel;

/*
 * rlog prints formatted text in various colors to easily distinguish the different logging
 * levels. This should not be called by itself.
 *
 * Input:
 *  LogLevel level: the type of log to be performed
 *  const char* m: the message to display in the log
 *
 * Output:
 *  Does not change the state
 */
void rlog(LogLevel level, const char* m, ...);

