#include <ucontext.h>
#include <support.h>
#include <cthread.h>
#include <cdata.h>

#include <stdbool.h>
#include <stdio.h>

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
    char dispatcher_stack[SIGSTKSZ];

    getcontext(&dispatcher);
    dispatcher.uc_link = 0;
    dispatcher.uc_stack.ss_sp = dispatcher_stack;
    dispatcher.uc_stack.ss_size = sizeof(dispatcher_stack);
    makecontext(&dispatcher, (void (*)(void))dispatch_thread, 0);

    // initialize thread queues
    CreateFila2(&queue_thread_ready);
    CreateFila2(&queue_thread_blocked);

    // save main thread context
    TCB_t thread_main;
    thread_main.tid = 0; // tid for the main thread must be zero
    thread_main.state = PROCST_EXEC;
    thread_main.ticket = random_ticket();
    getcontext(&thread_main.context);

    thread_running = &thread_main;

    cthread_init = true;
}

// TO-DO: catch possible errors and return error code
int ccreate(void* (*start)(void*), void *arg)
{
    if(!cthread_init)
    {
        initialize();
    }

    char new_thread_stack[SIGSTKSZ];

    TCB_t new_thread;
    new_thread.tid = tid_counter;
    tid_counter++;

    new_thread.state = PROCST_APTO;
    new_thread.ticket = random_ticket();

    getcontext(&new_thread.context);
    new_thread.context.uc_link = &dispatcher;
    new_thread.context.uc_stack.ss_sp = new_thread_stack;
    new_thread.context.uc_stack.ss_size = sizeof(new_thread_stack);
    makecontext(&new_thread.context, (void (*)(void))start, 1, arg);

    AppendFila2(&queue_thread_ready, (void*)&new_thread);

    return new_thread.tid;
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
