/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:55:11 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/29 22:15:42 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *info)
{
	t_philo	*ph;

	ph = (t_philo *)info;
	sleep_odds(ph);
	while (1)
	{
		LOCK(&ph->data->death_status);
		if (one(ph) == 0 || ph->data->status == 1 || ph->data->done_eating == 1)
			return (UNLOCK(&ph->data->death_status), NULL);
		UNLOCK(&ph->data->death_status);
		printing("is thinking", ph);
		pick_first_fork(ph);
		pick_second_fork(ph);
		printing("is eating", ph);
		lower_lines(ph);
		LOCK(&ph->data->death_status);
		if (ph->data->status == 1 || ph->data->done_eating == 1)
			return (UNLOCK(&ph->data->death_status), NULL);
		UNLOCK(&ph->data->death_status);
		printing("is sleeping", ph);
		ft_usleep(ph->data->t_sleep, ph->data);
	}
	return (NULL);
}

void	main_thread(t_info *info)
{
	int	tmp;
	int	j;

	while (info->status == 0 && info->done_eating == 0)
	{
		j = -1;
		check_eated_meals(info);
		while (++j < info->num)
		{
			LOCK(&info->dead);
			LOCK(&info->tmp);
			tmp = info->philo[j].time_since_eat;
			UNLOCK(&info->tmp);
			if ((ft_time() - info->start) - tmp > (unsigned int) info->t_die)
			{
				LOCK(&info->death_status);
				info->status = 1;
				UNLOCK(&info->death_status);
				print_death(info, j);
				break ;
			}
			UNLOCK(&info->dead);
		}
		usleep(400);
	}
}

int	main(int ac, char **av)
{
	t_info	info;
	int		i;

	if (ac == 5 || ac == 6)
	{
		if (init_info(&info, av, ac) == 1)
			return (write(2, "Invalid arguments\n", 18), 1);
		if (init_philo(&info) == 1)
			return (write(2, "Error while starting program\n", 29), free_info(&info), 1);
		init_mutexes(&info);
		i = -1;
		while (++i < info.num)
			pthread_create(&info.philo[i].th, NULL, routine, &info.philo[i]);
		check_eated_meals(&info);
		main_thread(&info);
		i = -1;
		while (++i < info.num)
			pthread_join(info.philo[i].th, NULL);
		free_info(&info);
		return (0);
	}
	else
		print_error();
	return (1);
}
