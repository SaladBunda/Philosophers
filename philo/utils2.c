/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:29:26 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/27 18:57:45 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(size_t milliseconds, t_info *info)
{
	size_t	start;
	int		tmp;
	int		tmp2;

	start = ft_time();
	while ((ft_time() - start) < milliseconds)
	{
		LOCK(&info->check_meals);
		tmp = info->done_eating;
		UNLOCK(&info->check_meals);
		LOCK(&info->death_status);
		tmp2 = info->status;
		UNLOCK(&info->death_status);
		if (tmp2 == 1 || tmp == 1)
			break ;
		usleep(400);
	}
	return (0);
}

void	printing(char *str, t_philo *ph)
{
	LOCK(&ph->data->print);
	LOCK(&ph->data->death_status);
	if (ph->data->status != 1)
		printf("%u %d %s\n", ft_time() - ph->data->start, ph->i + 1, str);
	UNLOCK(&ph->data->death_status);
	UNLOCK(&ph->data->print);
}

void	put_fork(t_philo *philo)
{
	UNLOCK(&philo->data->forks[philo->i]);
	UNLOCK(&philo->data->forks[(philo->i + 1) % philo->data->num]);
}

void	update_time(t_philo *philo)
{
	LOCK(&philo->data->tmp);
	philo->time_since_eat = ft_time() - philo->data->start;
	UNLOCK(&philo->data->tmp);
}
