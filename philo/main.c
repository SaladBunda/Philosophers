/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:04:39 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/04 02:32:46 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int mails = 0;

void *bunda(void *info)
{	
	t_info *info_cast = (t_info *)info;
	struct timeval tv;
	pthread_mutex_t mutex = info_cast->mutex;
	gettimeofday(&tv, NULL);
    long milliseconds = tv.tv_usec / 1000;
	for(long i = 0 ; i < 100; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	printf("%ld\n",milliseconds);
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

int	main(int ac, char **av)
{
	t_info info;

	if(ac == 5 || ac == 6)
	{
		pthread_mutex_init(&info.mutex, NULL);
		init_info(&info, av, ac);
		info.philo = malloc(sizeof(t_philo) * info.num);		
		if(!info.philo)
			return 0;
		int i;
		while(not_dead(info))
		{
			i = -1;
			while(++i < info.num)
				pthread_create(&info.philo[i].th,NULL,(void *)bunda,(void *)&info);
			i = -1;
			while(++i < info.num)
				pthread_join(info.philo[i].th,NULL);
		}
		
		printf("%d\n",mails);
		return 0;
	}
	return 1;
}