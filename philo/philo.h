/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:18:04 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/25 02:35:37 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

# define LOCK pthread_mutex_lock
# define UNLOCK pthread_mutex_unlock

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
	pthread_t	th;
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
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
	pthread_mutex_t	tmp;
	pthread_mutex_t	meals;
	pthread_mutex_t	t_eaten;
	pthread_mutex_t	check_meals;
	pthread_mutex_t	death_status;
}	t_info;

int				ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
int				ft_atoi(char *s, int *error);
unsigned int	ft_time(void);
int				ft_usleep(size_t milliseconds, t_info *info);
void			printing(char *str, t_philo *ph);
void			put_fork(t_philo *philo);
void			update_time(t_philo *philo);
int				one(t_philo *philo);
void			sleep_odds(t_philo *philo);
void			pick_first_fork(t_philo *philo);
void			pick_second_fork(t_philo *philo);
void			increment_meals(t_philo *philo);
void			test_arg(t_info *info, int *error);
int				init_info(t_info *info, char **av, int ac);
void			check_eated_meals(t_info *info);
int				init_philo(t_info *info);
void			init_mutexes(t_info *info);
void			free_info(t_info *info);
void			lower_lines(t_philo *info_cast);
void			print_death(t_info *info, int j);
void			print_error(void);

#endif