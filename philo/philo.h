#ifndef PHILO_H
# define PHILO_H


# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
// # include <time.h>
#include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	int eating;
	int sleeping;
	int thinking;
	int forks;
	int alive;
	int index;
	pthread_t th;
} t_philo;

typedef struct s_info
{
	int num;
	int t_die;
	int t_eat;
	int t_sleep;
	int t_to_eat;
	t_philo *philo;
	pthread_mutex_t mutex;
}	t_info;

int	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int	ft_atoi(char *s);


#endif