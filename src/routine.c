/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:05:52 by erivero-          #+#    #+#             */
/*   Updated: 2023/09/01 12:13:28 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

/* void socorro(t_thdata *philo)
{
	long	act;
	long	last;
	long	die;

	act = get_time();
	last = (long)philo->last_meal;
	die = (long)philo->info->time_to_die;
	printf("actual time is %li\n last meal was %li\n, time to die is %li\n", act, last, die);
} */

static void	*monitorize(void *philo_ptr)
{
	t_thdata	*philo;

	philo = (t_thdata *)philo_ptr;
	while (1)
	{
		if (get_time() - philo->last_meal > philo->info->time_to_die) // >=?
		{
			philo->info->monitor = false;
			print_status(philo, 'd');
			return (NULL);
		}
 		if (philo->info->eat_times > 0)
		{
			if (philo->eat_count == philo->info->eat_times)
				philo->info->feeded_philos++;
			if (philo->info->feeded_philos == philo->info->nop)
			{				
				philo->info->monitor = false;
				break ;
			} 
		}
	}
	return (NULL);
}


static void	*routine(void *philo_ptr)
{
	t_thdata	*philo;
	pthread_t	mon;

	philo = (t_thdata *)philo_ptr;
	philo->last_meal = get_time();
	pthread_create(&mon, NULL, &monitorize, philo);
/* 	if (philo->id % 2 == 0)
		usleep(1); */
	while (philo->info->monitor)
	{
		ft_think(philo);
		ft_eat(philo);
		ft_sleep(philo);
	}
	pthread_join(mon, NULL);
	return (NULL);
}

/* void	one_philo(t_main *info)
{
	if (pthread_create(&info->tid[0], NULL, &routine, NULL))
		printf("Error creating threads\n");
	else
} */


int	ft_threads(t_main *info)
{
	int	i;

	i = -1;
	info->start_time = get_time();
	info->feeded_philos = 0;
/* 	if (info->nop == 1)
		one_philo(info); */
	while (++i < info->nop)
	{
		if (pthread_create(&info->tid[i], NULL, &routine, &info->philos[i]))
		{
			printf("Error creating threads\n");
			return (0);
		}
	}
	i = -1;
	while (++i < info->nop)
	{
		if (pthread_join(info->tid[i], NULL))
		{
			printf("Error joining threads\n");
			break ;
		}
	}
	return (0);
}
