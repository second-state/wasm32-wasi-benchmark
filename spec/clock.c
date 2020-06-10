#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void test_clock(const char *name, const clockid_t id) {
  struct timespec spec;
  int result;
  result = clock_getres(CLOCK_REALTIME, &spec);
  if (result < 0) {
    printf("clock_getres(%s) failed, ret=%d, %s\n", name, result,
           strerror(errno));
  } else {
    printf("clock_getres(%s) = %llu.%09lu\n", name, spec.tv_sec, spec.tv_nsec);
  }

  result = clock_gettime(CLOCK_REALTIME, &spec);
  if (result < 0) {
    printf("clock_gettime(%s) failed, ret=%d, %s\n", name, result,
           strerror(errno));
  } else {
    printf("clock_gettime(%s) = %llu.%09lu\n", name, spec.tv_sec, spec.tv_nsec);
  }
}

int main(int argc, char *argv[]) {
  test_clock("CLOCK_REALTIME", CLOCK_REALTIME);
  test_clock("CLOCK_MONOTONIC", CLOCK_MONOTONIC);
  test_clock("CLOCK_PROCESS_CPUTIME_ID", CLOCK_PROCESS_CPUTIME_ID);
  test_clock("CLOCK_THREAD_CPUTIME_ID", CLOCK_THREAD_CPUTIME_ID);
  return EXIT_SUCCESS;
}
