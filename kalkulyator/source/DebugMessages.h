/*
 * DebugMessages.h
 *
 *  Created on: Mar 29, 2016
 *      Author: rober
 */

#ifndef SOURCE_DEBUGMESSAGES_H_
#define SOURCE_DEBUGMESSAGES_H_

#include <cstdio>
#include <cstdarg>

extern void panic(const char *fmt, ...) __attribute__ ((noreturn));
extern void vpanic(const char *fmt, va_list ap) __attribute__ ((noreturn));

#endif /* SOURCE_DEBUGMESSAGES_H_ */
