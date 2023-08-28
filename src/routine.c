/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:05:52 by erivero-          #+#    #+#             */
/*   Updated: 2023/08/28 16:40:18 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/* void	print_status(int status)
{
	if (status == 'f')
		printf("")
} */

void	eat(t_thdata *philo)
{
	if (philo->info->nop % 2 != 0 && philo->id == philo->info->nop)
	{
		pthread_mutex_lock(philo->rfork)
		print_status();
		pthread_mutex_lock(philo->lfork)
		print_status();
	}
	else
	{
		pthread_mutex_lock(philo->lfork)
//		print_status();
		pthread_mutex_lock(philo->rfork)
//		print_status();
	}
//	print_status(eat);
	usleep(philo->info->time_to_eat * 1000);
	philo->eat_count++;
//	philo-> last_meal / time_left / whatever ya veremos
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

void	ft_threads(t_main	*info)
{
	int	i;

	i = 0;
	info->start_time = ft_time();
	while (i < info->nop)
	{
		if (pthread_create(&info->tid[i], NULL, &routine, NULL))
		{
			printf("Error creating threads\n");
			break ;
		}
		i++;
	}
	i = 0;
	while (i < info->nop)
	{
		if (pthread_join(info->tid[i], NULL))
		{
			printf("Error joining threads\n");
			break ;
		}
		i++;
	}
}
