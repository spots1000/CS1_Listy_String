// Sean Szumlanski
// COP 3502, Fall 2018

// =========================
// ListyString: testcase28.c
// =========================
// Unit test for printListyString(): Test the printing of a NULL ListyString.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListyString.h"

int unit_test(int argc, char **argv)
{
	printListyString(NULL);
	printf("Length: %d\n", listyLength(NULL));

	return 0;
}
