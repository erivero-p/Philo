/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:47:59 by erivero-          #+#    #+#             */
/*   Updated: 2023/09/08 12:56:22 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*meal_check(void *info_ptr)
{
	t_main	*info;

	info = (t_main *)info_ptr;
	pthread_mutex_lock(&info->locker);
	while (1)
	{
		if (info->fed_philos == info->nop)
		{
//			usleep(1);
			info->monitor = false;
			break ;
		}
	}
	pthread_mutex_unlock(&info->locker);
	return (NULL);
}

void	*monitorize(void *philo_ptr)
{
	t_thdata	*philo;

	philo = (t_thdata *)philo_ptr;
	pthread_mutex_lock(&philo->info->locker);
	while (1)
	{
		if (get_time() - philo->last_meal > philo->info->time_to_die)
		{
			print_status(philo, 'd');
			philo->info->monitor = false;
			break ;
		}
	}
	pthread_mutex_unlock(&philo->info->locker);
	return (NULL);
}
