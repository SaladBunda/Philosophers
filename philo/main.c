/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:04:39 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/08 01:24:09 by ael-maaz         ###   ########.fr       */
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

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = ft_time();
	while ((ft_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

int not_dead(t_info info)
{
	int i = 0;
	while(i < info.num)
	{
		if(info.philo[i].alive != 1)
			return (1);
		i++;
	}
	return 0;
}
void *bunda(void *info)
{	
	static int boo = 1;
	t_philo *info_cast = (t_philo *)info;
	unsigned int start_time = info_cast->data->start_time;
	if((info_cast->index % 2) != 0 && boo ==1)
	{
		printf("%u %d is sleeping\n",ft_time() - start_time,info_cast->index);
		ft_usleep((info_cast->data->t_sleep)/4);
		boo++;
	}

	// printf("%d     %d\n",info_cast->times_eaten,info_cast->data->t_to_eat);
	while(info_cast->data->status != 1 && info_cast->times_eaten < info_cast->data->t_to_eat)
	{
		pthread_mutex_lock(&info_cast->data->forks[info_cast->index]);
		if(info_cast->data->status != 1)
			printf("%u %d has taken a fork\n",ft_time() - start_time,info_cast->index);
		pthread_mutex_lock(&info_cast->data->forks[(info_cast->index + 1) % info_cast->data->num]);
		if(info_cast->data->status != 1)
			printf("%u %d has taken a fork\n",ft_time() - start_time,info_cast->index);
		if(info_cast->data->status != 1)
			printf("%u %d is eating\n",ft_time() - start_time,info_cast->index);
		info_cast->times_eaten++;
		info_cast->time_since_eat = ft_time();
		ft_usleep(info_cast->data->t_eat);
		pthread_mutex_unlock(&info_cast->data->forks[info_cast->index]);
		pthread_mutex_unlock(&info_cast->data->forks[(info_cast->index + 1) % info_cast->data->num]);
		if(info_cast->data->status != 1)
			printf("%u %d is sleeping\n",ft_time() - start_time,info_cast->index);
		ft_usleep(info_cast->data->t_sleep);
		if(info_cast->data->status != 1)
			printf("%u %d is thinking\n",ft_time() - start_time,info_cast->index);
		if(ft_time() - info_cast->time_since_eat > (unsigned int) info_cast->data->t_die)
		{
			pthread_mutex_lock(&info_cast->data->dead);
			if(info_cast->data->status == 0)
			{
				info_cast->data->status = 1;
				printf("%u %d died \n", ft_time() - start_time, info_cast->index);
			}
			pthread_mutex_unlock(&info_cast->data->dead);
			return NULL;
		}
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
		info->t_to_eat = 123456789;
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

	if(ac == 5 || ac == 6)
	{
		init_info(&info, av, ac);
		info.forks = malloc(sizeof(pthread_mutex_t) * info.num);
		if(!info.forks)
			return 0;
		int i = -1;
		info.philo = malloc(sizeof(t_philo) * info.num);
		if(!info.philo)
			return 0;
		init_philo(&info);
		pthread_mutex_init(&info.dead, NULL);
		while(++i < info.num)
			pthread_mutex_init(&info.forks[i], NULL);
		i = -1;
		while(++i < info.num)
			pthread_create(&info.philo[i].th,NULL,(void *)bunda,(void *)&info.philo[i]);
		if(info.status == 1)
			return 0;
		i = -1;
		while(++i < info.num)
			pthread_join(info.philo[i].th,NULL);
		return 0;
	}
	return 1;
}