/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:41:39 by erivero-          #+#    #+#             */
/*   Updated: 2023/09/09 12:57:35 by erivero-         ###   ########.fr       */
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
	pthread_mutex_destroy(&info->mutex->locker);
	pthread_mutex_destroy(&info->mutex->write);
	pthread_mutex_destroy(&info->mutex->eat);
	pthread_mutex_destroy(&info->mutex->last_meal);
	free (info->mutex);
}

static void	philo_clean(t_main *info)
{
	if (info->tid)
		free(info->tid);
	if (info->philos)
		free(info->philos);
	if (info->forks)
		mutex_clean(info);
}

/* void	check_leakss(void)
{
	system("leaks -q philo");
} */

int	main(int ac, char **av)
{
	t_main	info;

//	atexit(check_leakss);
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
