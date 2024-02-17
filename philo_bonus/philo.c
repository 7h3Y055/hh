#include "philo.h"

int     philo(t_arg *ptr)
{
    int i;
    int tmp_id;

    i = -1;

    while (++i < ptr->philos_number)
    {
        usleep(500);
        ptr->philo[i].pid = fork();
        if (ptr->philo[i].pid == 0)
        {
            if (ptr->eat_times == 0)
                return (0);
            routine(&ptr->philo[i]);
        }
    }

    while (1)
    {
        i = -1;
        while (++i < ptr->philos_number)
        {
            if (waitpid(ptr->philo[i].pid, &ptr->pstatus, 0) > 0)
            {
                if (ptr->philo[i].status == 'f')
                    break ;
                tmp_id = i;
                i = -1;
                while (++i < ptr->philos_number)
                    if (i != tmp_id)
                        kill(ptr->philo[i].pid, SIGTERM);
                return (0);
            }
        }
    }
    return (0);
}

int     routine(t_philo *philo)
{
    int flag;
    pthread_t   th;
    pthread_create(&th, NULL, monitor, philo);
    flag = 1;
    while (1)
    {
        if ((get_time() - philo->last_eat > philo->arg->time_to_sleep + 200 || flag))
        {
            if (philo->status == 'f')
                exit(0);
            if (ft_take_forks(philo))
                return (1);
            if (ft_eat(philo))
                return (1);
            if (ft_sleep(philo))
                return (1);
            flag = 0;
        }
    }
    pthread_detach(th);
    return (0);
}

void    *monitor(void *addr)
{
    t_philo *philo;

    philo = addr;
    while (1)
    {
        if (philo->status != 'f' && get_time() - philo->last_eat > philo->arg->time_to_die)
        {
            print_status(philo, 'd');
            exit(0);
        }
        usleep(10000);
    }
}
