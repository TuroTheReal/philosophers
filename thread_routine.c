/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:55:00 by artberna          #+#    #+#             */
/*   Updated: 2024/09/25 10:05:30 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think_n_sleep_routine(t_phil *phil)
{
	if (check_end(phil->s_data))
		return ;
	write_status(phil, phil->id, "is sleeping. 😴");
	my_usleep(phil->s_data->time_sleep);
	if (check_end(phil->s_data))
		return ;
	write_status(phil, phil->id, "is thinking. 🤔");
}

static void	eat_routine(t_phil *phil)
{
	if (check_end(phil->s_data))
		return ;
	pthread_mutex_lock(&phil->left_fork);
	if (check_end(phil->s_data))
	{
		pthread_mutex_unlock(&phil->left_fork);
		return ;
	}
	write_status(phil, phil->id, "has taken a fork. 🥢");
	pthread_mutex_lock(phil->right_fork);
	if (check_end(phil->s_data))
	{
		pthread_mutex_unlock(phil->right_fork);
		pthread_mutex_unlock(&phil->left_fork);
		return ;
	}
	write_status(phil, phil->id, "has taken a fork. 🥢");
	write_status(phil, phil->id, "is eating. 🍜");
	pthread_mutex_lock(&phil->s_data->eat_mutex);
	pthread_mutex_lock(&phil->s_data->time_eat_mutex);
	phil->last_meal = get_current_time();
	phil->total_meal++;
	pthread_mutex_unlock(&phil->s_data->time_eat_mutex);
	pthread_mutex_unlock(&phil->s_data->eat_mutex);
	my_usleep(phil->s_data->time_eat);
	pthread_mutex_unlock(phil->right_fork);
	pthread_mutex_unlock(&phil->left_fork);
}

int	check_end(t_data *data)
{
	int	end;

	pthread_mutex_lock(&data->end_mutex);
	end = data->end_simulation;
	pthread_mutex_unlock(&data->end_mutex);
	return (end);
}

void	*routine(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	if (phil->s_data->nb_phil == 1)
		return (printf("0 1 died 💀\n"), NULL);
	if (phil->id % 2 == 0)
		my_usleep(100);
	while (!check_end(phil->s_data))
	{
		eat_routine(phil);
		think_n_sleep_routine(phil);
	}
	return (NULL);
}
