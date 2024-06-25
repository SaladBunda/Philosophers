/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:55:11 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/25 02:56:53 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*main_thread(void *fo)
{
	int	tmp;
	t_philo *info = (t_philo *)fo;
	while (1)
	{
			sem_wait(info->data->dead);
			sem_wait(info->data->tmp);
			tmp = info->time_since_eat;
			sem_post(info->data->tmp);
			if ((ft_time() - info->data->start) - tmp > (unsigned int) info->data->t_die)
			{
				info->data->status = 1;
				sem_wait(info->data->print);
				printf("%u %d ---------------------------------------------died\n", ft_time() - info->data->start, info->i + 1);
				sem_post(info->data->print);
				exit(1);
			}
			
			sem_post(info->data->dead);

			usleep(500);
	}
	return NULL;
}

void	*routine(void *info)
{
	t_philo	*info_cast;

	info_cast = (t_philo *)info;
	pthread_create(&info_cast->th, NULL,(void *)main_thread,info_cast);
	if (one_philo(info_cast) == 0)
		return (NULL);
	sleep_odds(info_cast);
	while (1)
	{
		if(info_cast->i == info_cast->data->num && info_cast->i % 2 == 0 && info_cast->times_eaten == info_cast->data->t_to_eat)
			exit(1);
		printing("is thinking", info_cast);
		pick_first_fork(info_cast);
		printing("is eating", info_cast);
		update_time(info_cast);
		ft_usleep(info_cast->data->t_eat, info_cast->data);
		info_cast->times_eaten++;
		put_fork(info_cast);
		// if((info_cast->i + 1) == info_cast->data->num /* && (info_cast->i + 1) % 2 == 0 */ && info_cast->times_eaten == info_cast->data->t_to_eat)
		// {
		// 	// printf("exiting ------------------------------------------------------------------------");
		// 	exit(1);
		// }
		printing("is sleeping", info_cast);
		ft_usleep(info_cast->data->t_sleep, info_cast->data);

		
		// printf("philo %d times eaten: %d    meals to eat:%d\n",info_cast->i,info_cast->times_eaten,info_cast->data->t_to_eat);
		// printf("philo %d | number of philo %d      is pair:%d          times eaten: %d | times to eat: %d\n",info_cast->i + 1,info_cast->data->num,(info_cast->i + 1) % 2,info_cast->times_eaten,info_cast->data->t_to_eat);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_info	info;
	int		i;

	// signal(SIGTERM, sigterm_handler);
	if (ac == 5 || ac == 6)
	{
		if (init_info(&info, av, ac) == 1)
			return (write(2, "Invalid arguments\n", 18), 1);
		
		if (init_philo(&info) == 1)
			return (write(2, "Error while starting program\n", 29), 1);
		if(init_mutexes(&info) == 1)
			return (1);
		i = -1;
		while (++i < info.num)
		{
			info.philo[i].th_fid = fork();
			
			if(info.philo[i].th_fid == 0)
			{
				routine(&info.philo[i]);
				exit(0);
			}
		}
		
		// i = -1;
		// while (++i < info.num)
		// {
		// 	sem_post(info.sim_start);
		// }


		// int total_meals = info.num * info.t_to_eat;
		// for (int j = 0; j < total_meals; j++)
		// {
		// 	sem_wait(info.meal_count);
		// 	while (++i < info.num)
		// 		{

		// 			kill(info.philo[i].th_fid, SIGKILL);
		// 		}
		// }

		 int status;

            waitpid(/* info.philo[j].th_fid */ 0, &status, 0);
			if (status != 0)
			{
			i = -1;
				while (++i < info.num)
				{

					kill(info.philo[i].th_fid, SIGKILL);
				}

			}
		return (0);
	}
	return (1);
}
