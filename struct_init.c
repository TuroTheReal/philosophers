/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:12:43 by artberna          #+#    #+#             */
/*   Updated: 2024/09/10 14:47:12 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	my_atol(char *str)
{
	long	nbr;
	int		sign;

	sign = 1;
	nbr = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (nbr < INT_MIN || nbr > INT_MAX)
			return (OVERFLOW);
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	return (sign * nbr);
}

static void	init_global_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->eat_mutex, NULL) != 0)
	{
		free_simulation(data, data->nb_phil);
		exit_error("Cannot create mutex");
	}
	if (pthread_mutex_init(&data->end_mutex, NULL) != 0)
	{
		free_simulation(data, data->nb_phil);
		exit_error("Cannot create mutex");
	}
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
	{
		free_simulation(data, data->nb_phil);
		exit_error("Cannot create mutex");
	}
	if (pthread_mutex_init(&data->time_eat_mutex, NULL) != 0)
	{
		free_simulation(data, data->nb_phil);
		exit_error("Cannot create mutex");
	}
}

static int	init_phil(t_data *data)
{
	int	i;

	i = 0;
	data->s_phil = malloc(sizeof(t_phil) * data->nb_phil);
	if (!data->s_phil)
		return (FALSE);
	if (memset(data->s_phil, 0, sizeof(t_phil) * data->nb_phil) == NULL)
		return (free(data->s_phil), FALSE);
	while (i < data->nb_phil)
	{
		data->s_phil[i].id = i + 1;
		data->s_phil[i].s_data = data;
		if (i == data->nb_phil - 1)
			data->s_phil[i].right_fork = &data->s_phil[0].left_fork;
		else
			data->s_phil[i].right_fork = &data->s_phil[i + 1].left_fork;
		if (pthread_mutex_init(&data->s_phil[i].left_fork, NULL) != 0)
		{
			free_simulation(data, i);
			exit_error("Cannot create mutex");
		}
		i++;
	}
	return (TRUE);
}

static int	init_struct_with_input(t_data *data, char **av)
{
	data->nb_phil = my_atol(av[1]);
	if (data->nb_phil < 1 || data->nb_phil == OVERFLOW)
		return (FALSE);
	data->time_die = my_atol(av[2]);
	if (data->time_die < 60 || data->time_die == OVERFLOW)
		return (FALSE);
	data->time_eat = my_atol(av[3]);
	if (data->time_eat < 60 || data->time_eat == OVERFLOW)
		return (FALSE);
	data->time_sleep = my_atol(av[4]);
	if (data->time_sleep < 60 || data->time_sleep == OVERFLOW)
		return (FALSE);
	if (av[5])
	{
		data->mandatory_meals = my_atol(av[5]);
		if (data->mandatory_meals < 1)
			return (FALSE);
	}
	data->start_time = get_current_time();
	return (TRUE);
}

void	init_struct(t_data *data, char **av)
{
	if (memset(data, 0, sizeof(t_data)) == NULL)
	{
		free(data);
		exit_error("Fail to initialisate memory");
	}
	if (init_struct_with_input(data, av) == FALSE)
	{
		free(data);
		printf("Incorrect input values\n");
		exit(EXIT_FAILURE);
	}
	if (init_phil(data) == FALSE)
	{
		free(data);
		exit_error("Fail to initialisate memory");
	}
	init_global_mutex(data);
}
