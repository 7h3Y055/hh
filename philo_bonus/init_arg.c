#include "philo.h"

static void    init_philos(t_arg *ptr);

int     init_arg(t_arg *ptr)
{
    sem_unlink("forks");
    sem_unlink("print");
    //semaphore for forks
    ptr->forks = sem_open("forks", O_CREAT, 0777, ptr->philos_number);
    //semaphore for printing
    ptr->print = sem_open("print", O_CREAT, 0777, 1);
    init_philos(ptr);
    ptr->start_time = get_time();
    ptr->finished_philos = 0;
    ptr->status = 'r';
    ptr->some_one_die = 0;
    return (0);
}

static void    init_philos(t_arg *ptr)
{
    int i;
    ptr->philo = malloc(sizeof(t_philo) * ptr->philos_number);
    i = 0;
    while (i < ptr->philos_number)
    {
        ptr->philo[i].id = i + 1;
        ptr->philo[i].eat_counter = 0;
        ptr->philo[i].last_eat = get_time();
        ptr->philo[i].status = 'r';
        ptr->philo[i].arg = ptr;
        i++;
    }
}

