#include <support.h>
#include <cthread.h>
#include <stdio.h>

void function1()
{
	printf("first thread executing function1\n");
}

void function2()
{
	printf("second thread executing function2\n");
}

int main(int argc, char **argv)
{
	printf("----- TEST 1 - ccreate - cjoin -----\n" \
		   "test the creation of cthreads, as well as the joins needed for\n" \
		   "the correct execution and ending of all cthreads\n\n");

	int tid1 = ccreate((void*(*)(void*))function1, 0);
	if (tid1)
	{
		printf("created thread with tid %d\n", tid1);
	}

	int tid2 = ccreate((void*(*)(void*))function2, 0);
	if (tid2)
	{
		printf("created thread with tid %d\n", tid2);
	}

	printf("main joining thread %d\n", tid1);
	if (cjoin(tid1) != 0)
	{
		printf("thread %d already finished\n", tid1);
	}

	printf("main joining thread %d\n", tid2);
	if (cjoin(tid2) != 0)
	{
		printf("thread %d already finished\n", tid2);
	}

	printf("returning to main thread to finish\n\n");

	printf("----- TEST 1 - ccreate - cjoin -----\n\n");

	return 0;
}
