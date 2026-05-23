/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 10:48:11 by jihi              #+#    #+#             */
/*   Updated: 2026/05/23 02:00:00 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_stop(t_data *data)
{
	int	value;

	pthread_mutex_lock(&data->m_stop);
	value = data->stop;
	pthread_mutex_unlock(&data->m_stop);
	return (value);
}

void	set_stop(t_data *data, int v)
{
	pthread_mutex_lock(&data->m_stop);
	data->stop = v;
	pthread_mutex_unlock(&data->m_stop);
}

void	set_ready(t_data *data, int v)
{
	pthread_mutex_lock(&data->m_stop);
	data->ready = v;
	pthread_mutex_unlock(&data->m_stop);
}

int	get_ready(t_data *data)
{
	int	value;

	pthread_mutex_lock(&data->m_stop);
	value = data->ready;
	pthread_mutex_unlock(&data->m_stop);
	return (value);
}
