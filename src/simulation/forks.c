/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:35:32 by jihi              #+#    #+#             */
/*   Updated: 2026/05/23 02:00:00 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	solo_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_table);
	philo->data->fork_busy[philo->left_i] = 1;
	pthread_mutex_unlock(&philo->data->m_table);
	print_state(philo->data, philo->id, TAKE_FORK);
	my_sleep(philo->data, philo->data->t_to_die);
	pthread_mutex_lock(&philo->data->m_table);
	philo->data->fork_busy[philo->left_i] = 0;
	pthread_mutex_unlock(&philo->data->m_table);
	return (1);
}

static void	start_eating(t_philo *philo)
{
	long	start;

	start = get_time();
	pthread_mutex_lock(&philo->m_state);
	philo->last_meal = start;
	philo->meal_end = start + philo->data->t_to_eat;
	pthread_mutex_unlock(&philo->m_state);
	print_state(philo->data, philo->id, TAKE_FORK);
	print_state(philo->data, philo->id, TAKE_FORK);
	print_state(philo->data, philo->id, EAT);
}

int	take_forks(t_philo *philo)
{
	if (get_stop(philo->data))
		return (1);
	if (philo->data->nb_philo == 1)
		return (solo_philo(philo));
	if (wait_forks(philo))
		return (1);
	start_eating(philo);
	return (0);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_table);
	philo->data->fork_busy[philo->left_i] = 0;
	philo->data->fork_busy[philo->right_i] = 0;
	pthread_mutex_unlock(&philo->data->m_table);
}
