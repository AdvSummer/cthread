#include <support.h>
#include <cthread.h>
#include <stdio.h>

static const int MAX_THREADS = 10;

void thread(void *i)
{
	printf("thread %d yielding\n", (int)i);
	cyield();
	printf("thread %d returning to finish\n", (int)i);
}

int main(int argc, char **argv)
{
	printf("----- TEST 2 - cyield -----\n" \
		   "test the correct execution of cyield, creating several threads\n" \
		   "that will yield in the middle of execution\n\n");

	int i;
	for (i = 1; i <= MAX_THREADS; ++i)
	{
		ccreate((void*(*)(void*))thread, (void*)i);
		printf("created thread with tid %d\n", i);
	}

	printf("main thread yielding\n");
	cyield();

	for (i = 1; i <= MAX_THREADS; ++i)
	{
		printf("main joining thread %d\n", i);
		cjoin(i);
	}

	printf("returning to main thread to finish\n\n");

	printf("----- TEST 2 - cyield -----\n\n");

	return 0;
}
