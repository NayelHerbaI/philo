/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 02:00:00 by jihi              #+#    #+#             */
/*   Updated: 2026/05/23 02:00:00 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	failed_forks(t_data *data, long init)
{
	long	i;

	i = 0;
	while (i < init)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	return (1);
}

int	setup_forks(t_data *data)
{
	long	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	data->init.alloc_forks = 1;
	data->fork_busy = malloc(sizeof(int) * data->nb_philo);
	if (!data->fork_busy)
		return (1);
	data->init.alloc_busy = 1;
	while (i < data->nb_philo)
	{
		data->fork_busy[i] = 0;
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (failed_forks(data, i));
		i++;
	}
	data->init.init_forks = 1;
	return (0);
}
