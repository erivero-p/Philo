/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:14:54 by erivero-          #+#    #+#             */
/*   Updated: 2023/09/04 10:33:54 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	philo_clean(t_main *info)
{
	int	i;

	i = -1;
	if (info->tid)
		free(info->tid);
	if (info->philos)
		free(info->philos);
	if (info->forks) // si ya hemos alojado memoria
	{
		if (&info->forks[0]) // si ya hemos creado un fork, creo que no está bien
		{
			while (++i < info->nop)
				pthread_mutex_destroy(info->forks);
		}
		free (info->forks);
	}
}

int	main(int ac, char **av)
{
	t_main	info;

	if (check_args(ac, av, &info))
	{
		if (ft_init(&info))
		{
			info.monitor = true;
			ft_threads(&info);
		}
		philo_clean(&info);
	}
	return (0);
}
