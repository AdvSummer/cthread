/*
 * cdata.h: arquivo de inclusão de uso apenas na geração da libpithread
 *
 * Esse arquivo pode ser modificado. ENTRETANTO, deve ser utilizada a TCB fornecida.
 *
 */
#ifndef __cdata__
#define __cdata__

#include <ucontext.h>

#define PROCST_CRIACAO  0
#define PROCST_APTO 1
#define PROCST_EXEC 2
#define PROCST_BLOQ 3
#define PROCST_TERMINO  4

#define MAX_TICKETS 256

/* NÃO ALTERAR ESSA struct */
typedef struct s_TCB { 
    int tid; // identificador da thread
    int state; // estado em que a thread se encontra
               // 0: Criação; 1: Apto; 2: Execução; 3: Bloqueado e 4: Término
    int ticket; // 0-255: bilhete de loteria da thread
    ucontext_t context; // contexto de execução da thread (SP, PC, GPRs e recursos)
} TCB_t; 

/*
 * Draw a ticket to be assigned to a thread or to select winning thread
 * the ticket is a number in the interval [0, MAX_TICKETS)
 */
unsigned int random_ticket();

#endif
