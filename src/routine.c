/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:05:52 by erivero-          #+#    #+#             */
/*   Updated: 2023/08/28 17:10:48 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_status(t_thdata *philo, char st)
{
	int		time;
	char	*status;

	time = ft_time() - philo->info->start_time;
	if (st == 'e')
		status = "is eating";
	if (st == 'f')
		status = "has taken a fork";
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
