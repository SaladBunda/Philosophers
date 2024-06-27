/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:29:26 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/27 11:35:11 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

	start = ft_time();
	while ((ft_time() - start) < milliseconds)
	{
		sem_wait(info->death_status);
		tmp = info->status;
		sem_post(info->death_status);
		if (tmp == 1)
			return (0);
		usleep(400);
	}
	return (0);
}

void	printing(char *str, t_philo *ph)
{
	int	tmp;

	sem_wait(ph->data->death_status);
	tmp = ph->data->status;
	sem_post(ph->data->death_status);
	sem_wait(ph->data->print);
	if (tmp != 1)
		printf("%u %d %s\n", ft_time() - ph->data->start, ph->i + 1, str);
	sem_post(ph->data->print);
}

void	put_fork(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	update_time(t_philo *philo)
{
	sem_wait(philo->data->tmp);
	philo->time_since_eat = ft_time() - philo->data->start;
	sem_post(philo->data->tmp);
}
