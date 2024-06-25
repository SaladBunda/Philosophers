/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 02:28:32 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/25 02:35:54 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_info(t_info *info)
{
	if (info->forks != NULL)
	{
		free(info->forks);
		info->forks = NULL;
	}
	if (info->philo != NULL)
	{
		free(info->philo);
		info->philo = NULL;
	}
}

void	lower_lines(t_philo *info_cast)
{
	update_time(info_cast);
	ft_usleep(info_cast->data->t_eat, info_cast->data);
	increment_meals(info_cast);
	put_fork(info_cast);
}

void	print_death(t_info *info, int j)
{
	LOCK(&info->print);
	printf("%u %d died\n", ft_time() - info->start, j + 1);
	UNLOCK(&info->print);
}

void	print_error(void)
{
	write(2, "Usage: ./philo (philos) (time to die) ", 39);
	write(2, "(time to eat) (time to sleep) (optional: meals)\n", 48);
}
