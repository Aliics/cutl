#include "../cutl.h"

#include <stdlib.h>
#include <unistd.h>

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


cutl_suite_start

describe_test("simple addition")
	given(x, 1)
	given(y, 2)

	when(plus(x, y))

	then(3)	
end_test

describe_test("string concat test")
	given(str0, "Hello, ")
	given(str1, "World!")

	when(string_concat(str0, str1))

	sleep(1);

	then("Hello, World!")
end_test

describe_test("some floats")
	given(f0, 2.5)
	given(f1, 0.5)

	when(f0 / f1)

	sleep(1);

	then(5.0)
end_test

cutl_suite_end
