/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:04:39 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/08 22:16:10 by ael-maaz         ###   ########.fr       */
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

int	ft_usleep(size_t milliseconds, t_info info)
{
	size_t	start;
	
	start = ft_time();
	while ((ft_time() - start) < milliseconds && info.status == 0)
		usleep(500);
	// while (1){
	// 	if((ft_time() - start) >= milliseconds || info.status == 1)
	// 	break;
	// 	usleep(500);
	// }
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

	t_philo *info_cast = (t_philo *)info;
	unsigned int start_time = info_cast->data->start_time;
	if((info_cast->index % 2) != 0 )
	{
		printf("%u %d is sleeping\n",ft_time() - start_time,info_cast->index);
		ft_usleep((info_cast->data->t_sleep),*info_cast->data);
	
	}

	while(1/* info_cast->data->status != 1 && info_cast->times_eaten < info_cast->data->t_to_eat */)
	{
		if(info_cast->data->status == 1)
			break;
		pthread_mutex_lock(&info_cast->data->forks[info_cast->index]);
		// if(info_cast->data->status != 1)
		// {
			pthread_mutex_lock(&info_cast->data->print);
			if(info_cast->data->status != 1)
				printf("%u %d has taken a fork\n",ft_time() - start_time,info_cast->index);
			pthread_mutex_unlock(&info_cast->data->print);
		// }
		pthread_mutex_lock(&info_cast->data->forks[(info_cast->index + 1) % info_cast->data->num]);
		// if(info_cast->data->status != 1)
		// {
			pthread_mutex_lock(&info_cast->data->print);
			if(info_cast->data->status != 1)
				printf("%u %d has taken a fork\n",ft_time() - start_time,info_cast->index);
			pthread_mutex_unlock(&info_cast->data->print);
		// }
		// if(info_cast->data->status != 1)
		// {
			pthread_mutex_lock(&info_cast->data->print);
			if(info_cast->data->status != 1)
				printf("%u %d is eating\n",ft_time() - start_time,info_cast->index);
			pthread_mutex_unlock(&info_cast->data->print);
			
		// }
		info_cast->times_eaten++;
		info_cast->time_since_eat = ft_time() - start_time;
		ft_usleep(info_cast->data->t_eat,*info_cast->data);
		pthread_mutex_unlock(&info_cast->data->forks[info_cast->index]);
		pthread_mutex_unlock(&info_cast->data->forks[(info_cast->index + 1) % info_cast->data->num]);
		// if(info_cast->data->status != 1)
		// {
			pthread_mutex_lock(&info_cast->data->print);
			if(info_cast->data->status != 1)
				printf("%u %d is sleeping\n",ft_time() - start_time,info_cast->index);
			pthread_mutex_unlock(&info_cast->data->print);
		// }
		ft_usleep(info_cast->data->t_sleep,*info_cast->data);
		// if(info_cast->data->status != 1)
		// {
			pthread_mutex_lock(&info_cast->data->print);
			if(info_cast->data->status != 1)
				printf("%u %d is thinking\n",ft_time() - start_time,info_cast->index);
			pthread_mutex_unlock(&info_cast->data->print);
		// }
		if(info_cast->data->status == 1)
			break;
		// if(ft_time() - info_cast->time_since_eat > (unsigned int) info_cast->data->t_die)
		// {
		// 	pthread_mutex_lock(&info_cast->data->dead);
		// 	if(info_cast->data->status == 0)
		// 	{
		// 		info_cast->data->status = 1;
		// 		printf("%u %d died \n", ft_time() - start_time, info_cast->index);
		// 	}
		// 	pthread_mutex_unlock(&info_cast->data->dead);
		// 	return NULL;
		// }
		// return NULL;
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
				if((ft_time() - info.start_time) - info.philo[j].time_since_eat > (unsigned int) info.t_die)
				{
						info.status = 1;
						pthread_mutex_lock(&info.print);
						printf("%u %d -----------------------------------died\n", ft_time() - info.start_time, j);
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