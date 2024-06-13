/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:39:08 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/13 00:11:33 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	test_arg(t_info *info, int *error)
{
	if (info->num <= 0 || info->num > 200)
		*error = 1;
	if (info->t_die < 60)
		*error = 1;
	if (info->t_eat < 60)
		*error = 1;
	if (info->t_sleep < 60)
		*error = 1;
}

int	init_info(t_info *info, char **av, int ac)
{
	int	error;

	error = 0;
	info->num = ft_atoi(av[1], &error);
	info->start = ft_time();
	info->t_die = ft_atoi(av[2], &error);
	info->t_eat = ft_atoi(av[3], &error);
	info->t_sleep = ft_atoi(av[4], &error);
	if (ac == 6)
		info->t_to_eat = ft_atoi(av[5], &error);
	else
		info->t_to_eat = -1;
	test_arg(info, &error);
	if (error != 0 || (ac == 6 && info->t_to_eat <= 0))
		return (1);
	return (0);
}

void	check_eated_meals(t_info *info)
{
	int	i;
	int	sum;

	i = -1;
	sum = 0;
	while (++i < info->num)
	{
		LOCK(&info->meals);
		sum += info->philo[i].times_eaten;
		UNLOCK(&info->meals);
	}
	if (sum == info->t_to_eat * info->num)
		info->done_eating = 1;
}

int	init_philo(t_info *info)
{
	int	i;

	info->forks = malloc(sizeof(pthread_mutex_t) * info->num);
	if (!info->forks)
		return (1);
	info->philo = malloc(sizeof(t_philo) * info->num);
	if (!info->philo)
		return (1);
	i = 0;
	info->status = 0;
	info->done_eating = 0;
	while (i < info->num)
	{
		info->philo[i].i = i;
		info->philo[i].alive = 1;
		info->philo[i].data = info;
		info->philo[i].time_since_eat = 0;
		info->philo[i].times_eaten = 0;
		i++;
	}
	return (0);
}

void	init_mutexes(t_info *info)
{
	int	i;

	i = -1;
	pthread_mutex_init(&info->dead, NULL);
	pthread_mutex_init(&info->print, NULL);
	pthread_mutex_init(&info->tmp, NULL);
	pthread_mutex_init(&info->meals, NULL);
	pthread_mutex_init(&info->t_eaten, NULL);
	while (++i < info->num)
		pthread_mutex_init(&info->forks[i], NULL);
}
