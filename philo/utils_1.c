#include "philo.h"

int    ft_eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->arg->mtx);
    pthread_mutex_lock(&philo->le_th);
    philo->last_eat = get_time();
    philo->eat_counter++;
    if (philo->eat_counter == philo->arg->eat_times)
        philo->status = 'f';
    pthread_mutex_unlock(&philo->arg->mtx);
    pthread_mutex_unlock(&philo->le_th);
    print_status(philo, 'e');
    
    ft_usleep(philo->arg->time_to_eat);

    
    pthread_mutex_unlock(philo->fork_1);
    pthread_mutex_unlock(philo->fork_2);
    pthread_mutex_lock(&philo->arg->mtx);
    if (philo->status == 'f' || philo->status == 'd')
    {
        philo->arg->finished_philos++;
        pthread_mutex_unlock(&philo->arg->mtx);
        return (1);
    }
    pthread_mutex_unlock(&philo->arg->mtx);
    return (0);
}

int ft_sleep_think(t_philo *philo)
{
    if (is_some_philo_die(philo->arg, 0))
        return (1);
    print_status(philo, 's');
    if (is_some_philo_die(philo->arg, 0))
        return (1);
    ft_usleep(philo->arg->time_to_sleep);
    pthread_mutex_lock(&philo->arg->m_status);
    if (philo->arg->status != 'd')
        return (1);
    pthread_mutex_unlock(&philo->arg->m_status);

    print_status(philo, 't');
    return (0);
}

int ft_take_forks(t_philo *philo)
{
    if (is_some_philo_die(philo->arg, 0))
        return (1);

    pthread_mutex_lock(philo->fork_1);

    if (is_some_philo_die(philo->arg, 0))
        return (1);

    print_status(philo, 'f');      

    if (is_some_philo_die(philo->arg, 0))
        return (1);

    pthread_mutex_lock(philo->fork_2);
    print_status(philo, 'f');
    return (0);
}