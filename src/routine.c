/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:05:52 by erivero-          #+#    #+#             */
/*   Updated: 2023/08/29 13:25:58 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	monitorize(void	*philo_ptr)
{
	t_thdata	*philo;

	philo = (t_thdata *)philo_ptr;
}

void	routine(void	*philo_ptr)
{
	t_thdata	*philo;
	pthread_t	monitor;

	philo = (t_thdata *)philo_ptr;
	pthread_create(&monitor, NULL, &monitorize, philo);
	while (//el monitor no se diga que se para)
	{
		//eat
		//sleep
		//think
	}
	pthread_join
}

void	ft_threads(t_main	*info)
{
	int	i;

	i = 0;
	info->start_time = ft_time();
	while (i < info->nop)
	{
		if (pthread_create(&info->tid[i], NULL, &routine, info->philos))
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
