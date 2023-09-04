/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:27:50 by erivero-          #+#    #+#             */
/*   Updated: 2023/09/04 12:09:29 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static bool	philo_alloc(t_main *info)
{
	info->tid = malloc(sizeof(pthread_t) * info->nop);
	info->philos = malloc(sizeof(t_thdata) * info->nop);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nop);
	if (!(info->tid && info->philos && info->forks)) //no sé si esto está bien así
	{
		printf("Error allocating memory\n");
		return (false);
	}
	return (true);
}

static bool	init_forks(t_main *info)
{
	int	i;

	i = 0;
	while (i < info->nop)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
		{
			printf("Error creating mutex\n");
			return (false);
		}
//		printf("a fork has been created\n");
		i++;
	}
	return (true);
}

static void	init_threads(t_main	*info)
{
	int	i;

	i = 0;
	while (i < info->nop)
	{
		info->philos[i].id = i + 1;
		info->philos[i].eat_count = 0;
		info->philos[i].info = info;
		info->philos[i].lfork = &info->forks[i];
		if (i == info->nop - 1)
			info->philos[i].rfork = &info->forks[0];
		else
			info->philos[i].rfork = &info->forks[i + 1];
		i++;
	}
}

bool	ft_init(t_main *info)
{
	if (!philo_alloc(info))
		return (false);
	if (!init_forks(info))
		return (false);
	init_threads(info);
	return (true);
}
