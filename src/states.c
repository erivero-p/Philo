/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:59:02 by erivero-          #+#    #+#             */
/*   Updated: 2023/08/29 11:21:54 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_status(t_thdata *philo, char st)
{
	int		time;
	char	*status;

	time = ft_time() - philo->info->start_time;
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
	printf("%ldms %d %s\n", time, philo->id, status);
}

void	eat(t_thdata *philo)
{
	if (philo->info->nop % 2 != 0 && philo->id == philo->info->nop)
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
	usleep(philo->info->time_to_eat * 1000);
	philo->eat_count++;
//	philo-> last_meal / time_left / whatever ya veremos
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

 