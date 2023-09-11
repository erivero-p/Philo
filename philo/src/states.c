/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:59:02 by erivero-          #+#    #+#             */
/*   Updated: 2023/09/11 10:07:12 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_think(t_thdata *philo)
{
	print_status(philo, 't');
}

static void	eat_counter(t_thdata *philo)
{
	if (philo->eat_count == philo->info->eat_times)
	{
		pthread_mutex_lock(&philo->info->mutex->eat);
		philo->info->fed_philos++;
		pthread_mutex_unlock(&philo->info->mutex->eat);
	}
}

void	take_forks(t_thdata *philo)
{
	if (philo->info->nop % 2 == 0)
	{
		pthread_mutex_lock(philo->rfork);
		print_status(philo, 'f');
		pthread_mutex_lock(philo->lfork);
		print_status(philo, 'f');
	}
	else
	{
		pthread_mutex_lock(philo->lfork);
		print_status(philo, 'f');
		pthread_mutex_lock(philo->rfork);
		print_status(philo, 'f');
	}
}

void	ft_eat(t_thdata *philo)
{
	take_forks(philo);
	print_status(philo, 'e');
	pthread_mutex_lock(&philo->info->mutex->last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->info->mutex->last_meal);
	usleep((philo->info->time_to_eat - 5) * 1000);
	philo->eat_count++;
	if (philo->info->eat_times > 0)
		eat_counter(philo);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

void	ft_sleep(t_thdata *philo)
{
	print_status(philo, 's');
	usleep(philo->info->time_to_sleep * 1000);
}
