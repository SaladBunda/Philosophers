/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:55:11 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/12 21:30:52 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define LOCK pthread_mutex_lock
#define UNLOCK pthread_mutex_unlock

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

void sleep_odds(t_philo *philo)
{
	if((philo->index % 2) != 0)
	{
		LOCK(&philo->data->print);
		if(philo->data->status != 1)
			printf("%u %d is sleeping\n",ft_time() - philo->data->start_time,philo->index + 1);
		UNLOCK(&philo->data->print);
		ft_usleep((philo->data->t_sleep),philo->data);
	}
}

void pick_first_fork(t_philo *philo)
{
	LOCK(&philo->data->forks[philo->index]);
	LOCK(&philo->data->print);
	if(philo->data->status != 1)
		printf("%u %d has taken a fork\n",ft_time() - philo->data->start_time,philo->index + 1);
	UNLOCK(&philo->data->print);
}

void pick_second_fork(t_philo *philo)
{
	LOCK(&philo->data->forks[(philo->index + 1) % philo->data->num]);
	LOCK(&philo->data->print);
	if(philo->data->status != 1)
		printf("%u %d has taken a fork\n",ft_time() - philo->data->start_time,philo->index + 1);
	UNLOCK(&philo->data->print);
}

void printing(char *str, t_philo *philo)
{
	LOCK(&philo->data->print);
	if(philo->data->status != 1)
		printf("%u %d %s\n",ft_time() - philo->data->start_time,philo->index + 1,str);
	UNLOCK(&philo->data->print);
}

void put_fork(t_philo *philo)
{
	UNLOCK(&philo->data->forks[philo->index]);
	UNLOCK(&philo->data->forks[(philo->index + 1) % philo->data->num]);
}
void update_time(t_philo *philo)
{
	LOCK(&philo->data->tmp);
	philo->time_since_eat = ft_time() - philo->data->start_time;
	UNLOCK(&philo->data->tmp);
}

void increment_meals(t_philo *philo)
{
	LOCK(&philo->data->meals);
	philo->times_eaten++;
	UNLOCK(&philo->data->meals);
}

void *bunda(void *info)
{	
	t_philo *info_cast;

	info_cast = (t_philo *)info;
	if(one_philo(info_cast) == 0)
		return (NULL);
	sleep_odds(info_cast);
	while(1)
	{
		if(info_cast->data->status == 1 || info_cast->data->done_eating == 1)
			break;
		printing("is thinking",info_cast);
		pick_first_fork(info_cast);
		pick_second_fork(info_cast);
		printing("is eating",info_cast);
		increment_meals(info_cast);
		update_time(info_cast);
		ft_usleep(info_cast->data->t_eat,info_cast->data);
		put_fork(info_cast);
		printing("is sleeping",info_cast);
		ft_usleep(info_cast->data->t_sleep,info_cast->data);
		if(info_cast->data->status == 1 || info_cast->data->done_eating == 1)
			break;
	}
	return NULL;
}
void test_arg(t_info *info, int *error)
{
	if(info->num <= 0 || info->num > 200)
		*error = 1;
	if(info->t_die < 60)
		*error = 1;
	if(info->t_eat < 60)
		*error = 1;
	if(info->t_sleep < 60)
		*error = 1;
}

int init_info(t_info *info,char **av,int ac)
{
	int error;
	error = 0;
	info->num = ft_atoi(av[1],&error);
	info->start_time = ft_time();
	info->t_die = ft_atoi(av[2],&error);
	info->t_eat = ft_atoi(av[3],&error);
	info->t_sleep = ft_atoi(av[4],&error);
	if (ac == 6)
		info->t_to_eat = ft_atoi(av[5],&error);
	else
		info->t_to_eat = -1;
	test_arg(info,&error);
	if(error != 0 || (ac == 6 && info->t_to_eat <= 0))
		return 1;
	return 0;
}

void check_eated_meals(t_info *info)
{
	int i = -1;
	int sum = 0;
	while(++i < info->num)
	{
		LOCK(&info->meals);
		sum += info->philo[i].times_eaten;
		UNLOCK(&info->meals);

	}
	if(sum == info->t_to_eat * info->num)
		info->done_eating = 1;
}

void init_philo(t_info *info)
{
	int i = 0;
	info->status = 0;
	info->done_eating = 0;
	while(i < info->num)
	{
		info->philo[i].index = i;
		info->philo[i].alive = 1;
		info->philo[i].data = info;
		info->philo[i].time_since_eat = 0;
		info->philo[i].times_eaten = 0;
		i++;
	}
}

void leaks()
{
	system("leaks philo");
}

int	main(int ac, char **av)
{
	t_info info;
	int tmp;
	atexit(leaks);

	if(ac == 5 || ac == 6)
	{
		if(init_info(&info, av, ac) == 1)
			return (write(2,"Invalid arguments\n",18),1);
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
		pthread_mutex_init(&info.meals, NULL);
		pthread_mutex_init(&info.t_eaten, NULL);
		while(++i < info.num)
			pthread_mutex_init(&info.forks[i], NULL);
		i = -1;
		while(++i < info.num)
			pthread_create(&info.philo[i].th,NULL,(void *)bunda,(void *)&info.philo[i]);
		int j =-1;
		check_eated_meals(&info);

		while(info.status == 0 && info.done_eating == 0)
		{
			j = -1;
			check_eated_meals(&info);
			while(++j < info.num)
			{
				LOCK(&info.dead);
				LOCK(&info.tmp);
				tmp = info.philo[j].time_since_eat;
				UNLOCK(&info.tmp);
				if((ft_time() - info.start_time) - tmp > (unsigned int) info.t_die)
				{
						info.status = 1;
						LOCK(&info.print);
						printf("%u %d died\n", ft_time() - info.start_time, j + 1);
						UNLOCK(&info.print);
							break;
				}
				UNLOCK(&info.dead);
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