/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:23:51 by jihi              #+#    #+#             */
/*   Updated: 2026/05/23 02:00:00 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_start_time(t_data *data)
{
	long	i;

	i = 0;
	data->timers.start = get_time();
	while (i < data->nb_philo)
	{
		data->philos[i].last_meal = data->timers.start;
		i++;
	}
}

int	start_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]))
		{
			set_stop(data, 1);
			return (1);
		}
		data->init.threads++;
		i++;
	}
	set_start_time(data);
	set_ready(data, 1);
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->init.threads)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (0);
}
