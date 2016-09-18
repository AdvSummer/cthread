#include <cdata.h>

#include <support.h>
#include <stdlib.h>

unsigned int random_ticket()
{
    unsigned int bin_size = (CRAND_MAX + 1u) / MAX_TICKETS;
    unsigned int leftover = (CRAND_MAX + 1u) % MAX_TICKETS;

    unsigned int random_number;
    do
    {
        random_number = Random2();
    }
    while (random_number >= RAND_MAX + 1u - leftover);

    return random_number / bin_size;
}

int thread_exists(PFILA2 queue, int tid)
{
    TCB_t *thread;
    FirstFila2(queue);
    do
    {
        if (queue->it == 0)
        {
            break;
        }
        else
        {
            thread = (TCB_t*)GetAtIteratorFila2(queue);
            if (thread->tid == tid)
            {
                return 0;
            }
        }
    } while (NextFila2(queue) == 0);

    return -1;
}
