#include "philo.h"

int main(int argc, char const **argv)
{
    t_arg   ptr;

    if (argc == 5 || argc == 6)
    {
        if (check_arg(&ptr, argv))
            exit (1);
        if (init_arg(&ptr) == -1)
            return (1);
        ptr.pstatus = philo(&ptr);
    }
    else
    {
        char *help1 = "./philo number_of_philosophers time_to_die time_to_eat ";
        char *help2 = "time_to_sleep [number_of_times_each_philosopher_must_eat]";
        printf("[+] Usage\n\t%s%s\n", help1, help2);
    }
    clean_all(&ptr);
    return (ptr.pstatus);
}

void    clean_all(t_arg *ptr)
{
    sem_unlink("forks");
    sem_unlink("print");
    free(ptr->philo);
}