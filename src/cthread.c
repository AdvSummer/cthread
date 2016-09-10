#include <ucontext.h>
#include <support.h>
#include <cthread.h>
#include <cdata.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// bool that controls whether any cthread function has been called
// this is needed because we need to save the thread main context
static bool cthread_init = false;

// context for the dispatcher, it will be assigned to the uc_link of
// every thread, this way, when any thread finishes, this context
// will start to select a new thread for execution or end the program
static ucontext_t dispatcher;

// possible states for a thread
static TCB_t *thread_running;
static FILA2 queue_thread_ready;
static FILA2 queue_thread_blocked;

// tid  used to identify a thread
static int tid_counter = 1;

// thread dispatcher, responsible for drawing a ticket and selecting the
// thread with the closest ticket number to execution
static void* dispatch_thread(void *args)
{
    return 0;
}

static void initialize()
{
    // make a context for the thread dispatcher
    getcontext(&dispatcher);
    dispatcher.uc_link = 0;
    dispatcher.uc_stack.ss_sp = malloc(SIGSTKSZ);
    dispatcher.uc_stack.ss_size = SIGSTKSZ;
    makecontext(&dispatcher, (void (*)(void))dispatch_thread, 0);

    // initialize thread queues
    CreateFila2(&queue_thread_ready);
    CreateFila2(&queue_thread_blocked);

    // save main thread context
    TCB_t *thread_main = malloc(sizeof(TCB_t));
    thread_main->tid = 0; // tid for the main thread must be zero
    thread_main->state = PROCST_EXEC;
    thread_main->ticket = random_ticket();
    getcontext(&thread_main->context);

    thread_running = thread_main;

    cthread_init = true;
}

// TO-DO: catch possible errors and return error code
int ccreate(void* (*start)(void*), void *arg)
{
    if(!cthread_init)
    {
        initialize();
    }

    TCB_t *new_thread = malloc(sizeof(TCB_t));
    new_thread->tid = tid_counter;
    tid_counter++;

    new_thread->state = PROCST_APTO;
    new_thread->ticket = random_ticket();

    getcontext(&new_thread->context);
    new_thread->context.uc_link = &dispatcher;
    new_thread->context.uc_stack.ss_sp = malloc(SIGSTKSZ);
    new_thread->context.uc_stack.ss_size = SIGSTKSZ;
    makecontext(&new_thread->context, (void (*)(void))start, 1, arg);

    AppendFila2(&queue_thread_ready, (void*)&new_thread);

    setcontext(&new_thread->context);

    return new_thread->tid;
}

int cyield(void)
{
    if(!cthread_init)
    {
        initialize();
    }
    return 0;
}

int cjoin(int tid)
{
    if(!cthread_init)
    {
        initialize();
    }
    return 0;
}

int csem_init(csem_t *sem, int count)
{
    if(!cthread_init)
    {
        initialize();
    }
    return 0;
}

int cwait(csem_t *sem)
{
    if(!cthread_init)
    {
        initialize();
    }
    return 0;
}

int csignal(csem_t *sem)
{
    if(!cthread_init)
    {
        initialize();
    }
    return 0;
}
