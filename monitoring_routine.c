/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:40:18 by artberna          #+#    #+#             */
/*   Updated: 2024/09/25 10:08:41 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_death(t_phil *phil)
{
	int	i;

	i = 0;
	while (i < phil->s_data->nb_phil)
	{
		pthread_mutex_lock(&phil->s_data->eat_mutex);
		pthread_mutex_lock(&phil->s_data->time_eat_mutex);
		if (phil[i].total_meal != 0 && \
			(get_current_time() - phil[i].last_meal) > phil->s_data->time_die)
		{
			pthread_mutex_lock(&phil->s_data->end_mutex);
			if (phil->s_data->end_simulation == 0)
			{
				phil->s_data->end_simulation = 1;
				write_status(phil, phil[i].id, "died. 💀");
			}
			pthread_mutex_unlock(&phil->s_data->time_eat_mutex);
			pthread_mutex_unlock(&phil->s_data->end_mutex);
			pthread_mutex_unlock(&phil->s_data->eat_mutex);
			return ;
		}
		pthread_mutex_unlock(&phil->s_data->time_eat_mutex);
		pthread_mutex_unlock(&phil->s_data->eat_mutex);
		i++;
	}
	return ;
}

static void	check_full(t_phil *phil)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < phil->s_data->nb_phil)
	{
		pthread_mutex_lock(&phil->s_data->eat_mutex);
		if (phil[i].total_meal == phil->s_data->mandatory_meals)
			phil[i].full = 1;
		if (phil[i].full == 1)
			count++;
		pthread_mutex_unlock(&phil->s_data->eat_mutex);
		i++;
	}
	if (count == phil->s_data->nb_phil)
	{
		pthread_mutex_lock(&phil->s_data->end_mutex);
		phil->s_data->end_simulation = 1;
		printf("All philosophers are full.\n");
		pthread_mutex_unlock(&phil->s_data->end_mutex);
	}
}

void	*monitoring_routine(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	if (phil->s_data->nb_phil == 1)
		return (NULL);
	while (!check_end(phil->s_data))
	{
		check_death(phil);
		if (phil->s_data->mandatory_meals != 0)
			check_full(phil);
	}
	return (NULL);
}
