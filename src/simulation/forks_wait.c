/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 02:00:00 by jihi              #+#    #+#             */
/*   Updated: 2026/05/23 02:00:00 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	reserve_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->left_i;
	right = philo->right_i;
	pthread_mutex_lock(&philo->data->m_table);
	if (philo->data->fork_busy[left] || philo->data->fork_busy[right])
	{
		pthread_mutex_unlock(&philo->data->m_table);
		return (0);
	}
	philo->data->fork_busy[left] = 1;
	philo->data->fork_busy[right] = 1;
	pthread_mutex_unlock(&philo->data->m_table);
	return (1);
}

static void	touch_wait(t_philo *philo)
{
	if (philo->data->nb_philo == 1)
		return ;
	if (get_period(philo->data) > philo->data->t_to_die)
		return ;
	pthread_mutex_lock(&philo->m_state);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->m_state);
}

int	wait_forks(t_philo *philo)
{
	while (!get_stop(philo->data))
	{
		touch_wait(philo);
		if (reserve_forks(philo))
			return (0);
		usleep(1000);
	}
	return (1);
}
