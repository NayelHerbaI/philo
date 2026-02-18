/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:35:32 by jihi              #+#    #+#             */
/*   Updated: 2026/02/18 18:22:40 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	solo_philo(t_philo *philo)
{
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(philo->left);
		print_state(philo->data, philo->id, TAKE_FORK);
		return (1);
	}
	return (0);
}

static int	take_one_fork(t_data *data, pthread_mutex_t *mut, int id)
{
	pthread_mutex_lock(mut);
	print_state(data, id, TAKE_FORK);
	if (get_stop(data))
	{
		pthread_mutex_unlock(mut);
		return (1);
	}
	return (0);
}

int	take_forks(t_philo *philo)
{
	if  (get_stop(philo->data))
		return (1);
	if (solo_philo(philo))
		return (1);
	if (philo->id % 2 == 0)
	{
		if (take_one_fork(philo->data, philo->left, philo->id))
			return (1);
		if (take_one_fork(philo->data, philo->right, philo->id))
		{
			pthread_mutex_unlock(philo->left);
			return (1);
		}
	}
	else
	{
		if (take_one_fork(philo->data, philo->right, philo->id))
			return (1);
		if (take_one_fork(philo->data, philo->left, philo->id))
		{
			pthread_mutex_unlock(philo->right);
			return (1);
		}
	}
	return (0);
}

void	drop_forks(t_philo *philo)
{
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_unlock(philo->left);
		return ;
	}
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}