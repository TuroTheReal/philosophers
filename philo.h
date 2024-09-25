/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:25:05 by artberna          #+#    #+#             */
/*   Updated: 2024/09/10 14:46:51 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <string.h>

typedef struct s_phil	t_phil;

typedef struct s_data
{
	long			nb_phil;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			mandatory_meals;
	long			start_time;
	unsigned int	end_simulation;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	time_eat_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	end_mutex;
	t_phil			*s_phil;
	pthread_t		monitoring;
}					t_data;

typedef struct s_phil
{
	int				id;
	pthread_t		th_id;
	long			last_meal;
	unsigned int	total_meal;
	int				full;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*s_data;

}					t_phil;

typedef enum e_error
{
	TRUE = 1,
	FALSE = 0,
	OVERFLOW = -212122212211,
}	t_error;

typedef enum e_action
{
	INIT,
	DESTROY,
	CREATE,
	JOIN,
}	t_action;

// Structure Init
void	init_struct(t_data *data, char **av);

// Thread Init
void	start_threads(t_data *data);

// Utils
void	exit_error(char *message);
void	free_simulation(t_data *data, int index);
void	my_usleep(long time_in_ms);
long	get_current_time(void);
void	write_status(t_phil *phil, int id, char *message);

// Routine
void	*routine(void *arg);
void	*monitoring_routine(void *arg);
int		check_end(t_data *data);

#endif