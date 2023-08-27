/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:14:54 by erivero-          #+#    #+#             */
/*   Updated: 2023/08/25 12:50:06 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool one_philo(t_main *info)
{
	if (pthread_create(&info->tid[0], NULL))
		return (false);
	
}

int	main(int ac, char **av)
{
	t_main	info;

	if (check_args(ac, av, &info))
	{
		if (init(&info))
		{
			if (info->nop == 1)
				one_philo(&info);
			else
		}
/* 		Me conviene sacar de la función init la creación de hilos
		porque debería haber inicializado todo y considerar el caso de
		un solo philo antes de ponerme a crear y llamar la rutina */
	}
	ft_clean(info);
	return (0);
}