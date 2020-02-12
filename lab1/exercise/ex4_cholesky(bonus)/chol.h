#include <sys/time.h>

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <functional>
#include <stdlib.h>
#include <malloc.h>
#include <stdint.h>
#include <math.h>

#include <omp.h>

static inline unsigned long long
my_getticks ()
{
  struct timeval t;
  gettimeofday (&t, 0);
  return t.tv_sec * 1000000ULL + t.tv_usec;
}

static inline double
my_ticks_to_seconds (unsigned long long ticks)
{
  return ticks * 1.0e-6;
}