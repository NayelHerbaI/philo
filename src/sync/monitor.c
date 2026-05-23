/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 02:00:00 by jihi              #+#    #+#             */
/*   Updated: 2026/05/23 02:00:00 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	get_last_meal(t_philo *philo)
{
	long	last;

	pthread_mutex_lock(&philo->m_state);
	last = philo->last_meal;
	pthread_mutex_unlock(&philo->m_state);
	return (last);
}

static int	all_philos_are_full(t_data *data)
{
	long	i;

	if (data->nb_meals < 0)
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->philos[i].m_state);
		if (data->philos[i].eaten_meals < data->nb_meals)
		{
			pthread_mutex_unlock(&data->philos[i].m_state);
			return (0);
		}
		pthread_mutex_unlock(&data->philos[i].m_state);
		i++;
	}
	set_stop(data, 1);
	return (1);
}

static int	philo_is_dead(t_data *data, long i)
{
	if (get_time() - get_last_meal(&data->philos[i]) < data->t_to_die)
		return (0);
	set_stop(data, 1);
	print_death(data, data->philos[i].id);
	return (1);
}

void	monitor(t_data *data)
{
	long	i;

	while (!get_stop(data))
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (philo_is_dead(data, i))
				return ;
			i++;
		}
		if (all_philos_are_full(data))
			return ;
		usleep(1000);
	}
}
