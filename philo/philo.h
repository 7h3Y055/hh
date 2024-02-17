#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_arg t_arg;

typedef struct s_philo
{
    int             id;
    pthread_t       th;
    pthread_mutex_t *fork_1;
    pthread_mutex_t *fork_2;
    long            eat_counter;
    pthread_mutex_t le_th;
    long            last_eat;
    char            status;
    t_arg           *arg;
}   t_philo;

typedef struct s_arg
{
    long    philos_number;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    eat_times;
    long    start_time;
    long    finished_philos;
    char    status;

    int     some_one_die;

    t_philo *philo;
    pthread_mutex_t  *forks;
    pthread_mutex_t   mtx;
    pthread_mutex_t   m_status;

}   t_arg;



int     philo(t_arg *arg);
int     init_arg(t_arg *arg);
int     check_arg(t_arg *arg, char const **argv);
long    ft_atoil(char const *str);
long    get_time(void);
void    *routine(void *addr);
void    monitor(t_arg *ptr);
void    ft_usleep(long n);
void    print_status(t_philo *philo, char status);
int    ft_eat(t_philo *philo);
int    ft_sleep_think(t_philo *philo);
int ft_take_forks(t_philo *philo);
void    clean_all(t_arg *ptr);

int is_some_philo_die(t_arg *ptr, int flag);
#endif