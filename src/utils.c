/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:03:37 by erivero-          #+#    #+#             */
/*   Updated: 2023/08/28 12:48:07 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_clean(t_main *info)
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

long	ft_time(void)
{
	struct timeval	tv;

	getimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

/* void ft_error(char *str, t_main *info)
{
	printf("%s\n", str);
	ft_clean(info);
} */
