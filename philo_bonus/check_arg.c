#include "philo.h"

int     check_arg(t_arg *ptr, char const **argv)
{
    ptr->philos_number = ft_atoil(argv[1]);
    ptr->time_to_die = ft_atoil(argv[2]);
    ptr->time_to_eat = ft_atoil(argv[3]);
    ptr->time_to_sleep = ft_atoil(argv[4]);
    ptr->eat_times = ft_atoil(argv[5]);
    if (ptr->philos_number == -27 || ptr->time_to_die == -27 || \
        ptr->time_to_eat == -27 || ptr->time_to_sleep == -27 || \
        ptr->eat_times < -1)
        return (1);
    return (0);
}