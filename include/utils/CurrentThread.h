#pragma once

#include <cxxabi.h>
#include <execinfo.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

namespace utils {
namespace CurrentThread {

extern __thread int t_cachedTid;
extern __thread char t_tidString[32];
extern __thread int t_tidStringLength;
extern __thread const char *t_threadName;
extern __thread char t_isMainThread;
extern __thread pthread_t t_pthread_t;

int tid();
const char *tidString(); // for logging
int tidStringLength();   // for logging
const char *threadName();
char isMainThread();
pthread_t pthreadt();

std::string stackTrace(bool demangle);
void sleepUsec(int64_t usec); // for testing

} // namespace CurrentThread
} // namespace utils
