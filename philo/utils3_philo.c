/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:34:00 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/25 02:21:40 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one(t_philo *philo)
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
	LOCK(&philo->data->forks[philo->i]);
	LOCK(&philo->data->print);
	LOCK(&philo->data->death_status);
	if (philo->data->status != 1)
		printf("%u %d %s\n", ft_time() - philo->data->start, philo->i + 1, str);
	UNLOCK(&philo->data->death_status);
	UNLOCK(&philo->data->print);
}

void	pick_second_fork(t_philo *philo)
{
	char	*str;

	str = "has taken a fork";
	LOCK(&philo->data->forks[(philo->i + 1) % philo->data->num]);
	LOCK(&philo->data->print);
	if (philo->data->status != 1)
		printf("%u %d %s\n", ft_time() - philo->data->start, philo->i + 1, str);
	UNLOCK(&philo->data->print);
}

void	increment_meals(t_philo *philo)
{
	LOCK(&philo->data->meals);
	if (philo->times_eaten < philo->data->t_to_eat)
		philo->times_eaten++;
	UNLOCK(&philo->data->meals);
}
