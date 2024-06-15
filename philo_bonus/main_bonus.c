/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:55:11 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/15 20:17:00 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*main_thread(void *fo)
{
	int	tmp;
	t_philo *info = (t_philo *)fo;
	// int	j;
	while (1/* info->status == 0 *//*  && info->done_eating == 0 */)
	{
		// j = -1;
		// check_eated_meals(info);
		// while (++j < info->num)
		// {
			sem_wait(info->data->dead);
			// sem_wait(info->data->tmp);
			tmp = info->time_since_eat;
			// sem_post(info->data->tmp);
			if ((ft_time() - info->data->start) - tmp > (unsigned int) info->data->t_die)
			{
				// printf("time ot die is:%u\n",info->t_die);
				info->data->status = 1;
				sem_wait(info->data->print);
				printf("%u %d died\n", ft_time() - info->data->start, info->i + 1);
				sem_post(info->data->print);
				// kill(0, SIGTERM);  // Signal all child processes to terminate
				exit(1);
				// exit(1);
			}
			sem_post(info->data->dead);
		usleep(500);
	}
	// }
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
		// if (info_cast->data->status == 1/*  || info_cast->data->done_eating == 1 */)
		// 	break ;
		printing("is thinking", info_cast);
		
		pick_first_fork(info_cast);
		// pick_first_fork(info_cast);
		// pick_second_fork(info_cast);
		printing("is eating", info_cast);
		increment_meals(info_cast);
		update_time(info_cast);
		ft_usleep(info_cast->data->t_eat, info_cast->data);
		put_fork(info_cast);
		printing("is sleeping", info_cast);
		ft_usleep(info_cast->data->t_sleep, info_cast->data);
		// if (info_cast->data->status == 1/*  || info_cast->data->done_eating == 1 */)
		// 	break ;
	}
	return (NULL);
}

// void    cleanup(t_info *info)
// {
//     sem_close(info->forks);
//     sem_unlink("/forks");
//     sem_close(info->print);
//     sem_unlink("/print");
//     sem_close(info->dead);
//     sem_unlink("/dead");
//     sem_close(info->tmp);
//     sem_unlink("/tmp");
//     free(info->philo);
// }


// void *monitor(void *to_be_casted)
// {
// 	t_philo *philo = (t_philo *)
// }

int	main(int ac, char **av)
{
	t_info	info;
	int		i;

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
				// pthread_create(&info.philo[i].th, NULL,routine,&info.philo[i]);
				// main_thread(&info, i);
				exit(0);
			}
		}

		// int status;
		 int status;
        for (int j = 0; j < info.num; j++)
        {
            waitpid(info.philo[j].th_fid, &status, 0);
			if (status != 0)
			{
			i = -1;
				while (++i < info.num)
				{
					// sem_close(philo[i].race);
					// free(philo[i].v);
					kill(info.philo[i].th_fid, SIGINT);
				}
				break ;
			}
        }

        // i = -1;
        // while (++i < info.num)
        // {
        //     kill((pid_t)info.philo[i].th_fid, SIGTERM);
        // }
        // cleanup(&info);
			
				

		// }
		// check_eated_meals(&info);
		// main_thread(&info);
		// i = -1;
		// while (++i < info.num)
		// 	waitpid(info.philo[i].th, NULL);
		// free(info.forks);
		// free(info.philo);
		return (0);
		// while(1);
	}
	return (1);
}
