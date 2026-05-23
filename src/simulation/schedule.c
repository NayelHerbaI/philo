/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schedule.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 02:00:00 by jihi              #+#    #+#             */
/*   Updated: 2026/05/23 02:00:00 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_period(t_data *data)
{
	long	waves;
	long	period;

	waves = 2;
	if (data->nb_philo % 2)
		waves = 3;
	period = waves * data->t_to_eat;
	if (period < data->t_to_eat + data->t_to_sleep)
		period = data->t_to_eat + data->t_to_sleep;
	return (period);
}

static long	get_advance(t_data *data)
{
	long	advance;

	advance = 10;
	if (data->t_to_eat / 4 < advance)
		advance = data->t_to_eat / 4;
	if (advance < 1)
		advance = 1;
	return (advance);
}

static long	get_slot(t_philo *philo)
{
	if (philo->data->nb_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			return (philo->data->t_to_eat);
		return (0);
	}
	if (philo->id == philo->data->nb_philo)
		return (philo->data->t_to_eat * 2);
	if (philo->id % 2 == 0)
		return (philo->data->t_to_eat);
	return (0);
}

void	wait_turn(t_philo *philo, long round)
{
	long	target;
	long	left;

	target = philo->data->timers.start + get_slot(philo);
	target += round * get_period(philo->data);
	if (round > 0 || get_slot(philo) > 0)
		target -= get_advance(philo->data);
	while (!get_stop(philo->data))
	{
		left = target - get_time();
		if (left <= 0)
			break ;
		if (left > 3)
			usleep((left - 1) * 1000);
		else
			usleep(500);
	}
}

void	touch_turn(t_philo *philo)
{
	if (philo->data->nb_philo == 1)
		return ;
	if (get_period(philo->data) > philo->data->t_to_die)
		return ;
	pthread_mutex_lock(&philo->m_state);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->m_state);
}
