#include "../cutl.h"

#include <stdlib.h>

int plus(int a, int b) { return a + b; }
char *string_concat(char *s0, char *s1) {
	// Bad strcat implementation. Just for these tests.
	char *s2 = malloc(sizeof(char) * 100);
	int i = 0;
	int j = 0;
	for (; s0[i] != '\0'; ++i) s2[i] = s0[i];
	for (; s1[j] != '\0'; ++i,++j) s2[i] = s1[j];
	s2[++i] = '\0';
	return s2;
}


CUTL_SUITE_START

DESCRIBE_TEST("simple addition")
	GIVEN(x, 1)
	GIVEN(y, 2)

	WHEN(plus(x, y))

	THEN(3)	
END_TEST

DESCRIBE_TEST("string concat test")
	GIVEN(str0, "Hello, ")
	GIVEN(str1, "World!")

	WHEN(string_concat(str0, str1))

	THEN("Hello, World!")
END_TEST

DESCRIBE_TEST("some floats")
	GIVEN(f0, 2.5)
	GIVEN(f1, 0.5)

	WHEN(f0 / f1)

	THEN(5.0)
END_TEST

CUTL_SUITE_END
