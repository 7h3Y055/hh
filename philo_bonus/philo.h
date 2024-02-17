#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>

typedef struct s_arg t_arg;

typedef struct s_philo
{
    int             id;
    int             pid;
    pthread_t       monitor;
    long            eat_counter;
    long            last_eat;
    char            status;
    t_arg           *arg;
}   t_philo;

typedef struct s_arg
{
    int     pstatus;
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
    sem_t   *forks;
    sem_t   *print;
}   t_arg;


int     philo(t_arg *arg);
int     init_arg(t_arg *arg);
int     check_arg(t_arg *arg, char const **argv);
long    ft_atoil(char const *str);
long    get_time(void);
int     routine(t_philo *philo);
void    ft_usleep(long n);
int     ft_take_forks(t_philo *philo);
int     ft_eat(t_philo *philo);
int     ft_sleep(t_philo *philo);
void    *monitor(void *addr);
void    print_status(t_philo *philo, char status);
void    clean_all(t_arg *ptr);

#endif