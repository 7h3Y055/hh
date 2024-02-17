#include "philo.h"

static void    init_philos(t_arg *ptr);

int     init_arg(t_arg *ptr)
{
    int i;

    ptr->forks = malloc(sizeof(pthread_mutex_t) * ptr->philos_number);
    init_philos(ptr);
    pthread_mutex_init(&ptr->mtx, NULL);
    pthread_mutex_init(&ptr->m_status, NULL);
    i = -1;
    while (++i < ptr->philos_number)
        pthread_mutex_init(&ptr->forks[i], NULL);
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
        ptr->philo[i].fork_1 = &ptr->forks[(i + 1) % ptr->philos_number];
        ptr->philo[i].fork_2 = &ptr->forks[i];
        if (i % 2)
        {
            ptr->philo[i].fork_1 = &ptr->forks[i];
            ptr->philo[i].fork_2 = &ptr->forks[(i + 1) % ptr->philos_number];
        }
        ptr->philo[i].arg = ptr;
        pthread_mutex_init(&ptr->philo[i].le_th, NULL);
        i++;
    }
}

