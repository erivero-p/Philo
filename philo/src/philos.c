/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:06:21 by erivero-          #+#    #+#             */
/*   Updated: 2023/09/06 18:24:48 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static bool	ft_threads(t_main *info)
{
	int	i;

	i = -1;
	while (++i < info->nop)
	{
		if (pthread_create(&info->tid[i], NULL, routine, &info->philos[i]))
		{
			printf("Error creating threads\n");
			return (false);
		}
	}
	i = -1;
	while (++i < info->nop)
	{
		if (pthread_join(info->tid[i], NULL))
		{
			printf("Error joining threads\n");
			return (false);
		}
	}
	return (true);
}

void	one_philo(t_main *info)
{
	ft_think(&info->philos[0]);
	usleep(info->time_to_die * 1000);
	print_status(info->philos, 'd');
	info->monitor = false;
}

void	ft_philo(t_main *info)
{
	info->monitor = true;
	info->fed_philos = 0;
	info->start_time = get_time();
	if (info->nop == 1)
		one_philo(info);
}
