/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:24:58 by artberna          #+#    #+#             */
/*   Updated: 2024/09/23 15:16:57 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
	{
		printf("Input must be : \"./exe X X X X optionnal_X\" !\n");
		return (1);
	}
	else
	{
		data = malloc(sizeof(t_data));
		if (!data)
			exit_error("Fail to allocate memory");
		init_struct(data, av);
		start_threads(data);
		free_simulation(data, data->nb_phil);
	}
	return (0);
}
