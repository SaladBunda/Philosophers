#ifndef PHILO_H
# define PHILO_H


# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
// # include <time.h>
#include <stdlib.h>
# include <sys/time.h>

typedef struct s_info  t_info;

typedef struct s_philo
{
	int eating;
	int sleeping;
	int thinking;
	int alive;
	int index;
	int t_die;
	int t_eat;
	int t_sleep;
	int t_to_eat;
	int times_eaten;
	int time_since_eat;
	t_info	*data;
	pthread_t th;
	int right;
	int left;
} t_philo;

typedef struct s_info
{
	int num;
	int status;
	int t_die;
	int t_eat;
	int t_sleep;
	int t_to_eat;
	unsigned int start_time;
	t_philo *philo;
	pthread_mutex_t *forks;
	pthread_mutex_t dead;
	pthread_mutex_t print;
}	t_info;

int	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int	ft_atoi(char *s);


#endif