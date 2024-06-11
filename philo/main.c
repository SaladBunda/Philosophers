/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:55:11 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/11 02:51:30 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int ft_time(void)
{
	struct timeval tv;
	if(gettimeofday(&tv, NULL))
		return 0;
	return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(size_t milliseconds, t_info *info)
{
	size_t	start;
	
	start = ft_time();
	while ((ft_time() - start) < milliseconds)
	{
		if(info->status == 1)
			break;
		usleep(500);
	}
	return (0);
}

int one_philo(t_philo *philo)
{
	if(philo->data->num == 1)
	{
		printf("0 1 has taken a fork\n");
		ft_usleep(philo->t_die,philo->data);
		printf("%u 1 died\n", philo->t_die);
		return (0);
	}
	return (1);
}

void *bunda(void *info)
{	
	t_philo *info_cast;
	unsigned int start_time;

	info_cast = (t_philo *)info;
	start_time = info_cast->data->start_time;

	if(one_philo(info_cast) == 0)
		return (NULL);

	if((info_cast->index % 2) != 0)
	{
		pthread_mutex_lock(&info_cast->data->print);
		if(info_cast->data->status != 1)
			printf("%u %d is sleeping\n",ft_time() - start_time,info_cast->index);
		pthread_mutex_unlock(&info_cast->data->print);
		ft_usleep((info_cast->data->t_sleep),info_cast->data);
	}

	while(1)
	{
		if(info_cast->data->status == 1)
			break;
		pthread_mutex_lock(&info_cast->data->forks[info_cast->index]);

		pthread_mutex_lock(&info_cast->data->print);
		if(info_cast->data->status != 1)
			printf("%u %d has taken a fork\n",ft_time() - start_time,info_cast->index + 1);
		pthread_mutex_unlock(&info_cast->data->print);
		pthread_mutex_lock(&info_cast->data->forks[(info_cast->index + 1) % info_cast->data->num]);

		pthread_mutex_lock(&info_cast->data->print);
		if(info_cast->data->status != 1)
			printf("%u %d has taken a fork\n",ft_time() - start_time,info_cast->index + 1);
		pthread_mutex_unlock(&info_cast->data->print);
		pthread_mutex_lock(&info_cast->data->print);
		if(info_cast->data->status != 1)
			printf("%u %d is eating\n",ft_time() - start_time,info_cast->index + 1);
		pthread_mutex_unlock(&info_cast->data->print);
		info_cast->times_eaten++;
		pthread_mutex_lock(&info_cast->data->tmp);
		info_cast->time_since_eat = ft_time() - start_time;
		pthread_mutex_unlock(&info_cast->data->tmp);
		ft_usleep(info_cast->data->t_eat,info_cast->data);
		pthread_mutex_unlock(&info_cast->data->forks[info_cast->index]);
		pthread_mutex_unlock(&info_cast->data->forks[(info_cast->index + 1) % info_cast->data->num]);
		pthread_mutex_lock(&info_cast->data->print);
		if(info_cast->data->status != 1)
			printf("%u %d is sleeping\n",ft_time() - start_time,info_cast->index + 1);
		pthread_mutex_unlock(&info_cast->data->print);
		ft_usleep(info_cast->data->t_sleep,info_cast->data);
		pthread_mutex_lock(&info_cast->data->print);
		if(info_cast->data->status != 1)
			printf("%u %d is thinking\n",ft_time() - start_time,info_cast->index + 1);
		pthread_mutex_unlock(&info_cast->data->print);
		if(info_cast->data->status == 1)
			break;
	}
	return NULL;
}

void init_info(t_info *info,char **av,int ac)
{
	info->num = ft_atoi(av[1]);
	info->start_time = ft_time();
	info->t_die = ft_atoi(av[2]);
	info->t_eat = ft_atoi(av[3]);
	info->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->t_to_eat = ft_atoi(av[5]);
	else
		info->t_to_eat = -1;
}

void init_philo(t_info *info)
{
	int i = 0;
	info->status = 0;
	int (*forks)[2] = malloc(sizeof(int) * info->num);
	if(!forks)
		return ;
	while(i < info->num)
	{
		forks[i][0] = i;
		forks[i][1] = 0;
		info->philo[i].index = i;
		info->philo[i].alive = 1;
		info->philo[i].data = info;
		info->philo[i].time_since_eat = 0;
		info->philo[i].time_since_eat = 0;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_info info;
	int tmp;

	if(ac == 5 || ac == 6)
	{
		init_info(&info, av, ac);
		// unsigned int start_time = ft_time();
		info.forks = malloc(sizeof(pthread_mutex_t) * info.num);
		if(!info.forks)
			return 0;
		int i = -1;
		info.philo = malloc(sizeof(t_philo) * info.num);
		if(!info.philo)
			return 0;
		init_philo(&info);
		pthread_mutex_init(&info.dead, NULL);
		pthread_mutex_init(&info.print, NULL);
		pthread_mutex_init(&info.tmp, NULL);
		while(++i < info.num)
			pthread_mutex_init(&info.forks[i], NULL);
		i = -1;
		while(++i < info.num)
			pthread_create(&info.philo[i].th,NULL,(void *)bunda,(void *)&info.philo[i]);
		int j =-1;
		while(info.status == 0)
		{
			j = -1;
			while(++j < info.num)
			{
				pthread_mutex_lock(&info.dead);
				pthread_mutex_lock(&info.tmp);
				tmp = info.philo[j].time_since_eat;
				pthread_mutex_unlock(&info.tmp);
				if((ft_time() - info.start_time) - tmp > (unsigned int) info.t_die)
				{
						info.status = 1;
						pthread_mutex_lock(&info.print);
						printf("%u %d -----------------------------------died\n", ft_time() - info.start_time, j + 1);
						pthread_mutex_unlock(&info.print);
							break;

				}
				pthread_mutex_unlock(&info.dead);
			}
			 usleep(500);
		}
		i = -1;
		while(++i < info.num)
			pthread_join(info.philo[i].th,NULL);
		return 0;
	}
	return 1;
}