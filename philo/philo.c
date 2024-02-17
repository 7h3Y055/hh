#include "philo.h"

int     philo(t_arg *ptr)
{
    int i;
    // int n;

    i = -1;
    // n = ptr->philos_number;
    while (++i < ptr->philos_number)
    {
        if (pthread_create(&ptr->philo[i].th, NULL, routine, &ptr->philo[i]) != 0)
            return (-1);
        usleep(50);
        if (pthread_detach(ptr->philo[i].th) != 0)
            return (-1);
    }
    monitor(ptr);
    // i = -1;
    // while (++i < n)
    //     if (pthread_join(ptr->philo[i].th, NULL) != 0)
    //         return (-1);
    return (0);
}

int is_some_philo_die(t_arg *ptr, int flag)
{
    // if (flag)
    // {
    //     pthread_mutex_lock(&ptr->mtx);
    //     ptr->status =  'd';
    //     pthread_mutex_unlock(&ptr->mtx);
    // }
    // if (!flag)
    // {
    (void)flag;
    pthread_mutex_lock(&ptr->m_status);
    if (ptr->status == 'd')
    {
        pthread_mutex_unlock(&ptr->m_status);
        return (1);
    }
    pthread_mutex_unlock(&ptr->m_status);
    // }
    return (0);
}

void    *routine(void *addr)
{
    t_philo   *philo;

    philo = addr;
    if (philo->arg->eat_times == 0)
        return (NULL);
    if (philo->arg->philos_number % 2 && philo->id % 2 == 0)
        ft_usleep(philo->arg->time_to_eat + 50);
    while (1)
    {
        if (ft_take_forks(philo))
            return (NULL);
        if (ft_eat(philo))
            return (NULL);
        if (ft_sleep_think(philo))
            return (NULL);
        // printf(".");
    }
    return (NULL);
}

int is_die(t_philo *philo)
{
    int die;

    pthread_mutex_lock(&philo->le_th);
    die = get_time() - philo->last_eat > philo->arg->time_to_die;
    pthread_mutex_unlock(&philo->le_th);
    if (die)
        return (1);
    return (0);
}

void monitor(t_arg *ptr)
{
    int i;

    while (ptr->status != 'd')
    {
        i = 0;
        pthread_mutex_lock(&ptr->m_status);
        if (ptr->finished_philos == ptr->philos_number)
        {
            ptr->status = 'd';
            pthread_mutex_unlock(&ptr->m_status);
            break ;
        }
        pthread_mutex_unlock(&ptr->m_status);
        while (i < ptr->philos_number)
        {
            // pthread_mutex_lock(&ptr->mtx);
            if (ptr->philo[i].status != 'f' && is_die(&ptr->philo[i]))
            {
                // pthread_mutex_unlock(&ptr->mtx);
                // pthread_mutex_unlock(&ptr->philo[i].le_th);
                print_status(&ptr->philo[i], 'd');

                pthread_mutex_lock(&ptr->m_status);
                ptr->status = 'd';
                pthread_mutex_unlock(&ptr->m_status);
                // is_some_philo_die(ptr, 1);

                // printf("22222222222222222222\n");
                return ;
            }
            // pthread_mutex_unlock(&ptr->mtx);
            i++;
        }
    }
}


// void monitor(t_arg *ptr)
// {
//     int i;

//     while (ptr->status != 'd')
//     {
//         i = 0;
//         pthread_mutex_lock(&ptr->mtx);
//         if (ptr->finished_philos == ptr->philos_number)
//         {
//             ptr->status = 'd';
//             pthread_mutex_unlock(&ptr->mtx);
//             break ;
//         }
//         pthread_mutex_unlock(&ptr->mtx);
//         while (i < ptr->philos_number)
//         {
//             pthread_mutex_lock(&ptr->mtx);
//             if (ptr->philo[i].status != 'f' && is_die(&ptr->philo[i]))
//             {
//                 pthread_mutex_unlock(&ptr->mtx);
//                 // pthread_mutex_unlock(&ptr->philo[i].le_th);

//                 // pthread_mutex_lock(&ptr->mtx);
//                 print_status(&ptr->philo[i], 'd');
//                 is_some_philo_die(ptr, 1);

//                 // printf("22222222222222222222\n");
//                 return ;
//             }
//             pthread_mutex_unlock(&ptr->mtx);
//             i++;
//         }
//     }
// }

