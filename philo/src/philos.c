/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:06:21 by erivero-          #+#    #+#             */
/*   Updated: 2023/09/11 10:08:53 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_status(t_thdata *philo, char st)
{
	long	time;
	char	*status;

	time = get_time() - philo->info->start_time;
	status = NULL;
	pthread_mutex_lock(&philo->info->mutex->locker);
	if (philo->info->monitor)
	{
		pthread_mutex_unlock(&philo->info->mutex->locker);
		if (st == 'f')
			status = "has taken a fork";
		if (st == 'e')
			status = "is eating";
		if (st == 's')
			status = "is sleeping";
		if (st == 't')
			status = "is thinking";
		if (st == 'd')
			status = "has died";
		pthread_mutex_lock(&philo->info->mutex->write);
		printf("%ld %d %s\n", time, philo->id, status);
		pthread_mutex_unlock(&philo->info->mutex->write);
	}
	pthread_mutex_unlock(&philo->info->mutex->locker);
}

static void	one_philo(t_main *info)
{
	ft_think(&info->philos[0]);
	usleep(info->time_to_die * 1000);
	print_status(info->philos, 'd');
	info->monitor = false;
}

static void	*routine(void *philo_ptr)
{
	t_thdata	*philo;
	pthread_t	mon;

	philo = (t_thdata *)philo_ptr;
	philo->last_meal = get_time();
	pthread_create(&mon, NULL, monitorize, philo);
	if (philo->id % 2 == 0)
		usleep(1);
	while (1)
	{
		pthread_mutex_lock(&philo->info->mutex->locker);
		if (!philo->info->monitor)
		{
			pthread_mutex_unlock(&philo->info->mutex->locker);
			break ;
		}
		pthread_mutex_unlock(&philo->info->mutex->locker);
		ft_think(philo);
		ft_eat(philo);
		ft_sleep(philo);
	}
	pthread_join(mon, NULL);
	return (NULL);
}

static void	ft_threads(t_main *info)
{
	int	i;

	i = -1;
	while (++i < info->nop)
	{
		if (pthread_create(&info->tid[i], NULL, routine, &info->philos[i]))
		{
			printf("Error creating threads\n");
			return ;
		}
	}
	i = -1;
	while (++i < info->nop)
	{
		if (pthread_join(info->tid[i], NULL))
		{
			printf("Error joining threads\n");
			return ;
		}
	}
}

void	ft_philo(t_main *info)
{
	pthread_t	meal_checker;

	info->monitor = true;
	info->fed_philos = 0;
	info->start_time = get_time();
	if (info->nop == 1)
		one_philo(info);
	else
	{
		if (info->eat_times > 0)
		{
			pthread_create(&meal_checker, NULL, meal_check, info);
			pthread_detach(meal_checker);
		}
		ft_threads(info);
	}
}
