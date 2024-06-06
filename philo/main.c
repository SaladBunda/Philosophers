/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:04:39 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/06 18:35:32 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int mails = 0;

void *bunda(void *info)
{	
	t_philo *info_cast = (t_philo *)info;
	struct timeval tv;
	gettimeofday(&tv, NULL);
    long milliseconds = tv.tv_usec / 1000;
	// pthread_mutex_lock(&rmutex);
	// mails++;
	// pthread_mutex_unlock(&rmutex);
	printf("%ld tiem to die %d\n",milliseconds,info_cast->data->t_die);
	// printf("%ld    %d    picked up fork #%d with address%p and time to die is %d\n",milliseconds, info_cast->index,info_cast->forks[info_cast->index][0],&info_cast->forks[0],info_cast[info_cast->index].data->t_die);
	return NULL;
}
int not_dead(t_info info)
{
	int i = 0;
	while(i < info.num)
	{
		if(info.philo[i].alive != 0)
			return (1);
		i++;
	}
	return 0;
}

void init_info(t_info *info,char **av,int ac)
{
	info->num = ft_atoi(av[1]);
	info->t_die = ft_atoi(av[2]);
	info->t_eat = ft_atoi(av[3]);
	info->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->t_to_eat = ft_atoi(av[5]);
}

void init_philo(t_info *info)
{
	int i = 0;
	int (*forks)[2] = malloc(sizeof(int) * info->num);
	if(!forks)
		return ;
	while(i < info->num)
	{
		forks[i][0] = i;
		forks[i][1] = 0;
		info->philo[i].index = i;
		info->philo[i].alive = 1;
		// info->philo[i].t_die = info->t_die;
		// info->philo[i].t_eat = info->t_eat;
		// info->philo[i].t_sleep = info->t_sleep;
		// info->philo[i].t_to_eat = info->t_to_eat;
		info->philo[i].data = info;
		i++;
	}
	i = -1;
	while(++i < info->num)
		info->philo[i].forks = forks;
}

int	main(int ac, char **av)
{
	t_info info;

	if(ac == 5 || ac == 6)
	{
		pthread_mutex_init(&info.r_mutex, NULL);
		pthread_mutex_init(&info.l_mutex, NULL);
		init_info(&info, av, ac);
		info.philo = malloc(sizeof(t_philo) * info.num);
		init_philo(&info);		
		if(!info.philo)
			return 0;
		int i;
		while(not_dead(info) == 1)
		{
			i = -1;
			while(++i < info.num)
				pthread_create(&info.philo[i].th,NULL,(void *)bunda,(void *)&info.philo[i]);
			i = -1;
			while(++i < info.num)
				pthread_join(info.philo[i].th,NULL);
		}
		
		// printf("%d\n",mails);
		// return 0;
	}
	return 1;
}