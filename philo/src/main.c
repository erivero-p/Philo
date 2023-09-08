/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:41:39 by erivero-          #+#    #+#             */
/*   Updated: 2023/09/08 11:35:40 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

static void	mutex_clean(t_main *info)
{
	int	i;

	i = -1;
	while (++i < info->nop)
		pthread_mutex_destroy(&info->forks[i]);
	free (info->forks);
	pthread_mutex_destroy(&info->locker);
	pthread_mutex_destroy(&info->write);
	pthread_mutex_destroy(&info->eat);
}

static void	philo_clean(t_main *info)
{
	int	i;

	i = -1;
	if (info->tid)
		free(info->tid);
	if (info->philos)
		free(info->philos);
	if (info->forks)
		mutex_clean(info);

}

int	main(int ac, char **av)
{
	t_main	info;

	if (check_args(ac, av, &info))
	{
		if (ft_init(&info))
		{
			ft_philo(&info);
		}
		philo_clean(&info);
	}
	return (0);
}
