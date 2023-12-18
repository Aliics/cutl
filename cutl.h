#ifndef __CUTL_H__
#define __CUTL_H__

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int __streq__(char *a, char *b) { return strcmp(a, b) == 0; }
int __inteq__(int a, int b) { return a == b; }
int __floateq__(float a, float b) { return a == b; }
int __doubleeq__(double a, double b) { return a == b; }

#define __mk_show_fail__(id, a, b) { \
		char *s = malloc(sizeof(char) * 1000); \
		snprintf(s, 1000, id" != "id, a, b); \
		return s; \
	}

char *__mk_show_fail_str__(char *a, char *b) __mk_show_fail__("%s", a, b)
char *__mk_show_fail_int__(int a, int b) __mk_show_fail__("%d", a, b);
char *__mk_show_fail_float__(float a, float b) __mk_show_fail__("%f", a, b);
char *__mk_show_fail_double__(double a, double b) __mk_show_fail__("%f", a, b);

#define __varname__(varname) varname##__FILE__##__LINE__
#define __compare__(a, b) \
	_Generic((a), \
		char *: __streq__, \
		int: __inteq__, \
		float: __floateq__, \
		double: __doubleeq__\
	)(a, b)
#define __show_fail__(a, b) \
	_Generic((a), \
		char *: __mk_show_fail_str__, \
		int: __mk_show_fail_int__, \
		float: __mk_show_fail_float__, \
		double: __mk_show_fail_double__ \
	)(a, b)

#define CUTL_SUITE_START \
	int main(void) { \
		int __varname__(tests) = 0; \
		int __varname__(tests_passed) = 0; \
		printf("Running %s test suite:\n", __FILE__);

#define CUTL_SUITE_END \
		printf( \
			"passed: %d, failed: %d\n", \
			__varname__(tests_passed), \
			__varname__(tests) - __varname__(tests_passed)\
		); \
	}

#define DESCRIBE_TEST(test_name) { char *__test_name__ = test_name;
#define GIVEN(var, val) __typeof__(val) var = val;
#define WHEN(when_val) __typeof__(when_val) actual = when_val;
#define THEN(then_val) \
	if (!(__compare__(actual, then_val))) { \
		printf("\t\"%s\" failed (%s)\n", __test_name__, __show_fail__(actual, then_val)); \
	} else { \
		__varname__(tests_passed)++; \
		printf("\t\"%s\" passed\n", __test_name__); \
	}
#define END_TEST __varname__(tests)++; }

#endif
