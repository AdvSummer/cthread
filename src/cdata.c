#include <cdata.h>

#include <support.h>
#include <stdlib.h>

unsigned int random_ticket()
{
    unsigned int bin_size = (RAND_MAX + 1u) / MAX_TICKETS;
    unsigned int leftover = (RAND_MAX + 1u) % MAX_TICKETS;

    unsigned int random_number;
    do
    {
        random_number = Random2();
    }
    while(random_number >= RAND_MAX + 1u - leftover);

    return random_number / bin_size;
}
