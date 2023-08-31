/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:54:44 by erivero-          #+#    #+#             */
/*   Updated: 2023/08/31 11:21:31 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
//# include <signal.h>
# include <stdbool.h>

// # define INPUT_ERR "Program closed due to invalid imput"
struct	s_main;

typedef struct s_thdata
{
	struct s_main	*info;
	int				id;
	int				eat_count;
	int				last_meal;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
}	t_thdata;
//r_fork y l_fork son punteros porque son recursos compartidos
typedef struct s_main
{
	int				nop;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_times;
	int				feeded_philos;
	long			start_time;
	bool			monitor;
	pthread_t		*tid;
	t_thdata		*philos;
	pthread_mutex_t	*forks;
}	t_main;

// initializers and utils
bool	check_args(int ac, char **av, t_main *info);
bool	ft_init(t_main *info);
long	get_time(void);

// thread management
int		ft_threads(t_main *info);
void	print_status(t_thdata *philo, char st);
void	ft_think(t_thdata *philo);
void	ft_eat(t_thdata *philo);
void	ft_sleep(t_thdata *philo);

#endif