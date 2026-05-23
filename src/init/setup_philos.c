/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 02:00:00 by jihi              #+#    #+#             */
/*   Updated: 2026/05/23 02:00:00 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_one_philo(t_data *data, int i)
{
	data->philos[i].id = i + 1;
	data->philos[i].last_meal = 0;
	data->philos[i].meal_end = 0;
	data->philos[i].eaten_meals = 0;
	data->philos[i].data = data;
	data->philos[i].left_i = i;
	data->philos[i].right_i = (i + 1) % data->nb_philo;
	data->philos[i].left = &data->forks[i];
	data->philos[i].right = &data->forks[(i + 1) % data->nb_philo];
	if (pthread_mutex_init(&data->philos[i].m_state, NULL))
		return (1);
	data->init.philos++;
	return (0);
}

int	setup_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (1);
	data->init.alloc_philos = 1;
	while (i < data->nb_philo)
	{
		if (init_one_philo(data, i))
			return (1);
		i++;
	}
	return (0);
}
