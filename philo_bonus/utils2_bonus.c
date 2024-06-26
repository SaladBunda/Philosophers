/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:29:26 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/26 02:49:29 by ael-maaz         ###   ########.fr       */
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

	start = ft_time();
	while ((ft_time() - start) < milliseconds)
	{
		sem_wait(info->death_status);
		if (info->status == 1)
			return(sem_post(info->death_status), 0) ;
		sem_post(info->death_status);
		usleep(500);
	}
	return (0);
}

void	printing(char *str, t_philo *ph)
{
	sem_wait(ph->data->print);
	sem_wait(ph->data->death_status);
	if (ph->data->status != 1)
		printf("%u %d %s\n", ft_time() - ph->data->start, ph->i + 1, str);
		sem_post(ph->data->death_status);
	sem_post(ph->data->print);
}

void	put_fork(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	update_time(t_philo *philo)
{
	unsigned int time;
	sem_wait(philo->data->test);
	time = ft_time() ;
	sem_post(philo->data->test);
	
	// sem_wait(philo->data->tmp);
	philo->time_since_eat = time - philo->data->start;
	// sem_post(philo->data->tmp);
}
