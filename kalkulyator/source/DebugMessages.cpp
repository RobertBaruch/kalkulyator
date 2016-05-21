/*
 * DebugMessages.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: rober
 */

#include "DebugMessages.h"
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include "fsl_debug_console.h"

int printf(const char *fmt, ...) {
  va_list ap;
  int result;

  va_start(ap, fmt);
  result = DbgConsole_VPrintf(const_cast<char *>(fmt), ap);
  va_end(ap);

  return result;
}

int vprintf(const char *fmt, va_list ap) {
  return DbgConsole_VPrintf(const_cast<char *>(fmt), ap);
}

void panic(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vpanic(fmt, ap);
}

void vpanic(const char *fmt, va_list ap) {
  printf("PANIC: ");
  vprintf(fmt, ap);
  abort();
}
