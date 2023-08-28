/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:14:54 by erivero-          #+#    #+#             */
/*   Updated: 2023/08/28 11:48:57 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/* void	one_philo(t_main *info)
{
	if (pthread_create(&info->tid[0], NULL))
		printf("Error creating threads\n");
	else
		
} */

int	main(int ac, char **av)
{
	t_main	info;

	if (check_args(ac, av, &info))
	{
		if (init(&info))
		{
			if (info.nop == 1)
				one_philo(&info);
			else
				ft_threads(&info);
		}
	}
	if (&info)
		ft_clean(info);
	return (0);
}
