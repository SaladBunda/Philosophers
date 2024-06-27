/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:45:59 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/27 13:37:46 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	last_even(int num)
{
	if (num % 2 == 0)
		return (num);
	else
		return (num - 1);
}

void	exit_program(t_info *info)
{
	sem_unlink("/dead");
	sem_unlink("/print");
	sem_unlink("/tmp");
	sem_unlink("/forks");
	sem_unlink("/death_status");
	free(info->philo);
}

int	one_philo_process(t_info *info)
{
	if (info->num == 1)
	{
		info->philo[0].th_fid = fork();
		if (info->philo[0].th_fid == 0)
		{
			printf("0 1 has taken a fork\n");
			ft_usleep(info->t_die, info);
			printf("%u 1 died\n", info->t_die);
			exit(0);
		}
		return (1);
	}
	else
		return (0);
}