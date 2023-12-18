#ifndef __CUTL_H__
#define __CUTL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int __streq__(char *a, char *b) { return strcmp(a, b) == 0; }
int __inteq__(int a, int b) { return a == b; }
int __floateq__(float a, float b) { return a == b; }
int __doubleeq__(double a, double b) { return a == b; }

#define __mk_show_fail__(id, a, b)                                             \
  {                                                                            \
    char *s = (char *)malloc(sizeof(char) * 1000);                             \
    snprintf(s, 1000, id " != " id, a, b);                                     \
    return s;                                                                  \
  }

char *__mk_show_fail_str__(char *a, char *b)
  __mk_show_fail__("%s", a, b);
char *__mk_show_fail_int__(int a, int b) 
  __mk_show_fail__("%d", a, b)
char *__mk_show_fail_float__(float a, float b)
  __mk_show_fail__("%f", a, b);
char *__mk_show_fail_double__(double a, double b)
  __mk_show_fail__("%f", a, b);

#define __varname__(varname) varname##__FILE__##__LINE__
#define __compare__(a, b)                                                      \
  _Generic((a),                                                                \
      char *: __streq__,                                                       \
      int: __inteq__,                                                          \
      float: __floateq__,                                                      \
      double: __doubleeq__)(a, b)
#define __show_fail__(a, b)                                                    \
  _Generic((a),                                                                \
      char *: __mk_show_fail_str__,                                            \
      int: __mk_show_fail_int__,                                               \
      float: __mk_show_fail_float__,                                           \
      double: __mk_show_fail_double__)(a, b)

#define cutl_suite_start                                                       \
  int main(void) {                                                             \
    int __varname__(tests) = 0;                                                \
    int __varname__(tests_passed) = 0;                                         \
    unsigned long __test_suite_start_time__ = time(NULL);                      \
    printf("Running %s test suite:\n", __FILE__);

#define cutl_suite_end                                                         \
  unsigned long __test_suite_elapsed_time__ =                                  \
      time(NULL) - __test_suite_start_time__;                                  \
  printf("passed: %d, failed: %d (%lus)\n", __varname__(tests_passed),         \
         __varname__(tests) - __varname__(tests_passed),                       \
         __test_suite_elapsed_time__);                                         \
  }

#define describe_test(test_name)                                               \
  {                                                                            \
    char *__test_name__ = test_name;                                           \
    unsigned long __test_start_time__ = time(NULL);
#define given(var, val) __typeof__(val) var = val;
#define when(when_val) __typeof__(when_val) actual = when_val;
#define then(then_val)                                                         \
  unsigned long __test_elapsed_time__ = time(NULL) - __test_start_time__;      \
  if (!(__compare__(actual, then_val))) {                                      \
    printf("\t\"%s\" failed (%s) (%lus)\n", __test_name__,                     \
           __show_fail__(actual, then_val), __test_elapsed_time__);            \
  } else {                                                                     \
    __varname__(tests_passed)++;                                               \
    printf("\t\"%s\" passed (%lus)\n", __test_name__, __test_elapsed_time__);  \
  }
#define end_test                                                               \
  __varname__(tests)++;                                                        \
  }

#endif
