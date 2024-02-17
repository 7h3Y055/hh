#include "philo.h"

long    ft_atoil(char const *str)
{
    long    n;
    int     i;

    n = 0;
    i = 0;
    if (!str)
        return (-1);
    while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
        i++;
    while (str[i] && str[i] == '+')
        i++;
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (printf("[ERROR] Wrong input!\n"), -27);
        n = n * 10 + str[i] - '0';
        i++;
    }
    if (n > INT_MAX)
        return (-27);
    return (n);
}

long    get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec * 0.001));
}

void    ft_usleep(long n)
{
    long    start;

    start = get_time();
    while (get_time() < start + n)
        usleep(100);
}


void    print_status(t_philo *philo, char status)
{
    // sem_wait(philo->arg->print);
    if (status == 't')
        printf("%ld\t%d is thinking\n", get_time() - philo->arg->start_time, philo->id);
    else if (status == 'f')
        printf("%ld\t%d has taken a fork\n", get_time() - philo->arg->start_time, philo->id);
    else if (status == 'e')
        printf("%ld\t%d is eating\n", get_time() - philo->arg->start_time, philo->id);
    else if (status == 's')
        printf("%ld\t%d is sleeping\n", get_time() - philo->arg->start_time, philo->id);
    else if (status == 'd')
        printf("%ld\t%d died\n", get_time() - philo->arg->start_time, philo->id);
    // sem_post(philo->arg->print);
}
