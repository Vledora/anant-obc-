#include <stdio.h>
#include <sys/ioctl.h>

#include "query_ioctl.h"

void get_vars(int fd)
{
    query_arg_t q;

    if (ioctl(fd, QUERY_GET_VARIABLES, &q) == -1)
    {
        perror("query_apps ioctl get");
    }
    else
    {
        printf("Status : %d\n", q.status);
        printf("Dignity: %d\n", q.dignity);
        printf("Ego    : %d\n", q.ego);
    }
}
void clr_vars(int fd)
{
    if (ioctl(fd, QUERY_CLR_VARIABLES) == -1)
    {
        perror("query_apps ioctl clr");
    }
}