/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:47:59 by erivero-          #+#    #+#             */
/*   Updated: 2023/09/09 12:56:06 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*meal_check(void *info_ptr)
{
	t_main	*info;

	info = (t_main *)info_ptr;
	while (1)
	{
		pthread_mutex_lock(&info->mutex->eat);
		if (info->fed_philos == info->nop)
		{
			pthread_mutex_unlock(&info->mutex->eat);
			pthread_mutex_lock(&info->mutex->locker);
			info->monitor = false;
			pthread_mutex_unlock(&info->mutex->locker);
			break ;
		}
		pthread_mutex_unlock(&info->mutex->eat);
	}
	return (NULL);
}

void	*monitorize(void *philo_ptr)
{
	t_thdata	*philo;

	philo = (t_thdata *)philo_ptr;
	while (1)
	{
		pthread_mutex_lock(&philo->info->mutex->last_meal);
		if (get_time() - philo->last_meal > philo->info->time_to_die)
		{
			pthread_mutex_unlock(&philo->info->mutex->last_meal);
			print_status(philo, 'd');
			pthread_mutex_lock(&philo->info->mutex->locker);
			philo->info->monitor = false;
			pthread_mutex_unlock(&philo->info->mutex->locker);
			break ;
		}
		pthread_mutex_unlock(&philo->info->mutex->last_meal);
	}
	return (NULL);
}
