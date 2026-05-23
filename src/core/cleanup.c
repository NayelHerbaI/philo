/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 02:00:00 by jihi              #+#    #+#             */
/*   Updated: 2026/05/23 02:00:00 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_philos(t_data *data)
{
	int	i;

	i = 0;
	if (!data->init.alloc_philos)
		return ;
	while (i < data->init.philos)
	{
		pthread_mutex_destroy(&data->philos[i].m_state);
		i++;
	}
	free(data->philos);
}

static void	clean_shared(t_data *data)
{
	if (data->init.alloc_forks)
		free(data->forks);
	if (data->init.alloc_busy)
		free(data->fork_busy);
	if (data->init.m_table)
		pthread_mutex_destroy(&data->m_table);
	if (data->init.m_print)
		pthread_mutex_destroy(&data->m_print);
	if (data->init.m_stop)
		pthread_mutex_destroy(&data->m_stop);
}

void	clean_everything(t_data *data)
{
	long	i;

	i = 0;
	if (!data)
		return ;
	if (data->init.alloc_forks && data->init.init_forks)
	{
		while (i < data->nb_philo)
			pthread_mutex_destroy(&data->forks[i++]);
	}
	clean_shared(data);
	clean_philos(data);
	free(data);
}
