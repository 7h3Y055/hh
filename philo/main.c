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
        if (philo(&ptr) == -1)
        {
            clean_all(&ptr);
            return (1);
        }
    }
        // exit(0);
    else
    {
        char *help1 = "./philo number_of_philosophers time_to_die time_to_eat ";
        char *help2 = "time_to_sleep [number_of_times_each_philosopher_must_eat]";
        printf("[+] Usage\n\t%s%s\n", help1, help2);
    }
    // clean_all(&ptr);
    return (0);
}

void    clean_all(t_arg *ptr)
{
    int i;

    i = -1;
    pthread_mutex_destroy(&ptr->mtx);
    pthread_mutex_destroy(&ptr->m_status);
    while (++i < ptr->philos_number)
    {
        pthread_mutex_destroy(&ptr->philo[i].le_th);
        pthread_mutex_destroy(&ptr->forks[i]);
        i++;
    }
    free(ptr->forks);
    free(ptr->philo);
}