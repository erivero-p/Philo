/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:54:44 by erivero-          #+#    #+#             */
/*   Updated: 2023/08/28 16:22:00 by erivero-         ###   ########.fr       */
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
	int				time_left;
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
	long			start_time;
	pthread_t		*tid;
	t_thdata		*philos;
	pthread_mutex_t	*forks;
}	t_main;

#endif