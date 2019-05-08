#ifndef TRACE_H
#define TRACE_H

#include <stdio.h>

#ifdef DEBUG_TRACE_ON
#define DEBUG_LOG(format, ...) printf ("%s(%u) %s: " format, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define DEBUG_LOG(format, ...) 
#endif

#endif // TRACE_H