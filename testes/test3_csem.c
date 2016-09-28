#include <support.h>
#include <cthread.h>
#include <stdio.h>

static const int MAX_THREADS = 10;

static csem_t semaphore;

void thread(void *i)
{
	printf("thread %d tries to consume resource\n", (int)i);
	cwait(&semaphore);
	printf("thread %d yielding\n", (int)i);
	cyield();
	printf("thread %d returning to finish\n", (int)i);
	csignal(&semaphore);
	printf("thread %d freeing resource\n", (int)i);
}

int main(int argc, char **argv)
{
	printf("----- TEST 3 - csem -----\n" \
		   "test the correct execution of csem_init, cwait and csignal.\n" \
		   "several threads will execute cwait, cyield and csignal,\n" \
		   "in this order, these threads will share a single semaphore\n" \
		   "with only one resource available\n\n");

	printf("initializing semaphore\n");
	csem_init(&semaphore, 1);

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

	printf("----- TEST 3 - csem -----\n\n");

	return 0;
}
