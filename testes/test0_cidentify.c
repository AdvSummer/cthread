#include <support.h>
#include <cthread.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	printf("----- TEST 0 - cidentify -----\n" \
		   "tests cidentify with a buffer of size 100, which should print\n" \
		   "the names and numbers of the colaborators.\n\n");

	char buffer[100];
	if (cidentify(buffer, sizeof(buffer)) == 0)
	{
		printf("cidentify succeeds:\n");
		printf("%s\n", buffer);
	}

	printf("----- TEST 0 - cidentify -----\n\n");

	return 0;
}
