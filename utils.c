/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:12:50 by artberna          #+#    #+#             */
/*   Updated: 2024/09/25 10:00:42 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_simulation(t_data *data, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (pthread_mutex_destroy(&data->s_phil[i].left_fork) != 0)
			exit_error("Failed to destroy mutex 1");
		i++;
	}
	if (pthread_mutex_destroy(&data->eat_mutex) != 0)
		exit_error("Failed to destroy mutex 2");
	if (pthread_mutex_destroy(&data->end_mutex) != 0)
		exit_error("Failed to destroy mutex 3");
	if (pthread_mutex_destroy(&data->write_mutex) != 0)
		exit_error("Failed to destroy mutex 4");
	if (pthread_mutex_destroy(&data->time_eat_mutex) != 0)
		exit_error("Failed to destroy mutex 5");
	if (data->s_phil)
		free(data->s_phil);
	if (data)
		free(data);
}

void	exit_error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

long	get_current_time(void)
{
	struct timeval	time;
	long			to_return;

	if (gettimeofday(&time, NULL) != 0)
		exit_error("gettimeofday failed");
	to_return = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (to_return);
}

void	my_usleep(long time_in_ms)
{
	long	start_time;
	long	time_left;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < time_in_ms)
	{
		time_left = time_in_ms - (get_current_time() - start_time);
		if (time_left < 1)
			usleep(time_left * 1000);
		else
			usleep(100);
	}
}

void	write_status(t_phil *phil, int id, char *message)
{
	long	time;

	pthread_mutex_lock(&phil->s_data->write_mutex);
	time = get_current_time() - phil->s_data->start_time;
	printf("%ld %d %s\n", time, id, message);
	pthread_mutex_unlock(&phil->s_data->write_mutex);
}
