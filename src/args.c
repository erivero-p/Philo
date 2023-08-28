/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:14:54 by erivero-          #+#    #+#             */
/*   Updated: 2023/08/28 11:22:33 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ph_atoi(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - 48;
		i++;
	}
	if (str[i] == '\0')
		return (num);
	else
		return (-1);
}

void	print_args(void)
{
	printf("Wrong arguments, the program shall be executed as shown below:\n");
	printf("./philo number_of_philosophers time_to_die time_to_eat ");
	printf("time_to_sleep\nA 5th optional argument can be accepted as:");
	printf(" [number_of_times_each_philosopher_must_eat]\n");
}

/* void print_args(t_main *info)
{
	printf("%i\n", info->nop);
	printf("%i\n", info->time_to_die);
	printf("%i\n", info->time_to_eat);
	printf("%i\n", info->time_to_sleep);
	printf("%i\n", info->eat_times);
} */
bool	check_args(int ac, char **av, t_main *info)
{
	if (ac == 5 || ac == 6)
	{
		info->nop = ph_atoi(av[1]);
		info->time_to_die = ph_atoi(av[2]);
		info->time_to_eat = ph_atoi(av[3]);
		info->time_to_sleep = ph_atoi(av[4]);
		if (ac == 6)
			info->eat_times = ph_atoi(av[5]);
		else
			info->eat_times = -42;
	}
	if (ac < 5 || ac > 6 || info->time_to_die == -1 || info->time_to_eat == -1
		|| info->time_to_sleep == -1 || info->eat_times == -1
		|| info->nop == -1)
	{
		print_args();
		return (false);
	}
	else
		return (true);
}
