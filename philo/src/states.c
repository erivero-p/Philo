/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:59:02 by erivero-          #+#    #+#             */
/*   Updated: 2023/09/08 11:12:12 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_status(t_thdata *philo, char st)
{
	long	time;
	char	*status;

	time = get_time() - philo->info->start_time;
	status = NULL;
	pthread_mutex_lock(&philo->info->write);
	if (philo->info->monitor)
	{
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
		printf("%ld %d %s\n", time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->info->write);
}

void	ft_think(t_thdata *philo)
{
	print_status(philo, 't');
}

static void	eat_counter(t_thdata *philo)
{
	if (philo->eat_count == philo->info->eat_times)
	{
		pthread_mutex_lock(&philo->info->eat);
		philo->info->fed_philos++;
		pthread_mutex_unlock(&philo->info->eat);
	}
}

void	ft_eat(t_thdata *philo)
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
	print_status(philo, 'e');
	usleep((philo->info->time_to_eat - 5) * 1000);
	philo->eat_count++;
	if (philo->info->eat_times > 0)
		eat_counter(philo);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

void	ft_sleep(t_thdata *philo)
{
	print_status(philo, 's');
	usleep(philo->info->time_to_sleep * 1000);
}
