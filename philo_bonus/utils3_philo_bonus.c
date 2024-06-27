/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_philo_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:34:00 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/27 11:30:02 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	one_philo(t_philo *philo)
{
	if (philo->data->num == 1)
	{
		printf("0 1 has taken a fork\n");
		ft_usleep(philo->t_die, philo->data);
		printf("%u 1 died\n", philo->t_die);
		return (0);
	}
	return (1);
}

void	sleep_odds(t_philo *philo)
{
	if ((philo->i % 2) != 0)
	{
		printing("is sleeping", philo);
		ft_usleep((philo->data->t_sleep), philo->data);
	}
}

void	pick_first_fork(t_philo *philo)
{
	char	*str;

	str = "has taken a fork";
	sem_wait(philo->data->forks);
	sem_wait(philo->data->print);
	if (philo->data->status != 1)
		printf("%u %d %s\n", ft_time() - philo->data->start, philo->i + 1, str);
	sem_post(philo->data->print);
	sem_wait(philo->data->forks);
	sem_wait(philo->data->print);
	if (philo->data->status != 1)
		printf("%u %d %s\n", ft_time() - philo->data->start, philo->i + 1, str);
	sem_post(philo->data->print);
}
