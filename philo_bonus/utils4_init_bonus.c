/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_init_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:39:08 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/26 02:48:24 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	init_philo(t_info *info)
{
	int	i;

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

int	init_mutexes(t_info *info)
{
	int	i;

	i = -1;
	sem_unlink("/dead");
	sem_unlink("/test");
	sem_unlink("/print");
	sem_unlink("/tmp");
	sem_unlink("/meals");
	sem_unlink("/t_eaten");
	sem_unlink("/forks");
	sem_unlink("/meal_count");
	sem_unlink("/death_status");
	sem_unlink("/test");
	sem_unlink("/update_time");
	info->update_time = sem_open("/update_time", O_CREAT, 0644, 1);
    if (info->update_time == SEM_FAILED)
        return (1);
	info->test = sem_open("/test", O_CREAT, 0644, 1);
    if (info->test == SEM_FAILED)
        return (1);
	info->death_status = sem_open("/death_status", O_CREAT, 0644, 1);
    if (info->death_status == SEM_FAILED)
        return (1);
	info->meal_count = sem_open("/meal_count", O_CREAT, 0644, 0);
    if (info->meal_count == SEM_FAILED)
        return (1);
	info->forks = sem_open("/forks", O_CREAT, 0644, info->num);
	if(info->forks == SEM_FAILED)
		return(1);
	info->dead = sem_open("/dead", O_CREAT, 0644, 1);
	if(info->dead == SEM_FAILED)
		return(1);
	info->print = sem_open("/print", O_CREAT, 0644, 1);
	if(info->print == SEM_FAILED)
		return(1);
	info->tmp = sem_open("/tmp", O_CREAT, 0644, 1);
	if(info->tmp == SEM_FAILED)
		return(1);
	info->meals = sem_open("/meals", O_CREAT, 0644, 1);
	if(info->meals == SEM_FAILED)
		return(1);
	info->t_eaten = sem_open("/t_eaten", O_CREAT, 0644, 1);
	if(info->t_eaten == SEM_FAILED)
		return(1);
	return (0);
}
