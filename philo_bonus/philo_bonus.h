/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:18:04 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/26 19:55:21 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>


typedef struct s_info	t_info;

typedef struct s_philo
{
	int			eating;
	int			sleeping;
	int			thinking;
	int			alive;
	int			i;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			t_to_eat;
	int			times_eaten;
	int			time_since_eat;
	t_info		*data;
	int			th_fid;
	pthread_t			th;
}	t_philo;

typedef struct s_info
{
	int				num;
	int				status;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_to_eat;
	int				done_eating;
	unsigned int	start;
	t_philo			*philo;
	sem_t			*forks;
	sem_t			*dead;
	sem_t			*death_status;
	sem_t			*print;
	sem_t			*tmp;
	sem_t			*meals;
	sem_t			*t_eaten;
	sem_t			*meal_count;
    sem_t			*done_meals;
	sem_t			*sim_start;
	sem_t			*test;
	sem_t			*update_time;
	pthread_mutex_t		mutex_test;
	pthread_mutex_t		mutex_test2;
}	t_info;

int				ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
int				ft_atoi(char *s, int *error);
unsigned int	ft_time(void);
int				ft_usleep(size_t milliseconds, t_info *info);
void			printing(char *str, t_philo *ph);
void			put_fork(t_philo *philo);
void			update_time(t_philo *philo);
int				one_philo(t_philo *philo);
void			sleep_odds(t_philo *philo);
void			pick_first_fork(t_philo *philo);
void			test_arg(t_info *info, int *error);
int				init_info(t_info *info, char **av, int ac);
int				init_philo(t_info *info);
int				init_mutexes(t_info *info);
int				last_even(int num);
void			exit_program(t_info *info);

#endif