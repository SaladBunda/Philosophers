/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:55:11 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/27 16:52:01 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*main_thread(void *fo)
{
	int		tmp;
	t_philo	*info;

	info = (t_philo *)fo;
	while (1)
	{
		sem_wait(info->data->dead);
		sem_wait(info->data->tmp);
		tmp = info->time_since_eat;
		sem_post(info->data->tmp);
		if ((ft_time() - info->data->start) - tmp > (t_ui) info->data->t_die)
		{
			sem_wait(info->data->death_status);
			info->data->status = 1;
			sem_post(info->data->death_status);
			sem_wait(info->data->print);
			printf("%u %d died\n", ft_time() - info->data->start, info->i + 1);
			exit(1);
		}
		sem_post(info->data->dead);
		usleep(400);
	}
	return (NULL);
}

void	*routine(void *info)
{
	t_philo	*cst;

	cst = (t_philo *)info;
	pthread_create(&cst->th, NULL, (void *)main_thread, cst);
	if (one_philo(cst) == 0)
		return (NULL);
	sleep_odds(cst);
	while (1)
	{
		if ((cst->i + 1) == LE(cst->DT->num) && cst->t_eaten == cst->DT->tt_eat)
			exit(1);
		printing("is thinking", cst);
		pick_first_fork(cst);
		printing("is eating", cst);
		update_time(cst);
		ft_usleep(cst->DT->t_eat, cst->DT);
		cst->t_eaten++;
		put_fork(cst);
		if ((cst->i + 1) == LE(cst->DT->num) && cst->t_eaten == cst->DT->tt_eat)
			exit(1);
		printing("is sleeping", cst);
		ft_usleep(cst->DT->t_sleep, cst->DT);
	}
	return (NULL);
}

int	initiation(t_info *info, char **av, int ac)
{
	if (init_info(info, av, ac) == 1)
		return (write(2, "Invalid arguments\n", 18), 1);
	if (init_philo(info) == 1)
		return (write(2, "Error while starting program\n", 29), 1);
	if (init_mutexes(info) == 1)
		return (write(2, "error while initialising\n", 26), 1);
	return (0);
}

void	waiting(t_info *info)
{
	int	i;
	int	status;

	waitpid(0, &status, 0);
	if (status != 0)
	{
		i = -1;
		while (++i < info->num)
			kill(info->philo[i].th_fid, SIGKILL);
	}
}

int	main(int ac, char **av)
{
	t_info	info;
	int		i;

	if (ac == 5 || ac == 6)
	{
		if (initiation(&info, av, ac) == 1)
			return (1);
		i = -1;
		if (one_philo_process(&info) == 1)
			return (exit_program(&info), 0);
		while (++i < info.num)
		{
			info.philo[i].th_fid = fork();
			if (info.philo[i].th_fid == 0)
			{
				routine(&info.philo[i]);
				exit(0);
			}
		}
		waiting(&info);
		exit_program(&info);
		return (0);
	}
	else
		print_error();
}
