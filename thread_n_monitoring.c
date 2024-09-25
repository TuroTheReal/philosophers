/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_n_monitoring.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:51:05 by artberna          #+#    #+#             */
/*   Updated: 2024/09/09 11:41:13 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_monitoring(t_data *data)
{
	if (pthread_create(&data->monitoring, NULL, \
	&monitoring_routine, data->s_phil) != 0)
	{
		free_simulation(data, data->nb_phil);
		exit_error("phtread_create failed");
	}
	if (pthread_join(data->monitoring, NULL) != 0)
	{
		free_simulation(data, data->nb_phil);
		exit_error("phtread_join failed");
	}
}

void	start_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_phil)
	{
		if (pthread_create(&data->s_phil[i].th_id, NULL, \
		&routine, &data->s_phil[i]) != 0)
		{
			free_simulation(data, data->nb_phil);
			exit_error("phtread_create failed");
		}
		i++;
	}
	start_monitoring(data);
	i = 0;
	while (i < data->nb_phil)
	{
		if (pthread_join(data->s_phil[i].th_id, NULL) != 0)
		{
			free_simulation(data, data->nb_phil);
			exit_error("phtread_join failed");
		}
		i++;
	}
}
