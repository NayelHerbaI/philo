/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:17:30 by jihi              #+#    #+#             */
/*   Updated: 2026/05/23 02:00:00 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	get_meal_end(t_philo *philo)
{
	long	end;

	pthread_mutex_lock(&philo->m_state);
	end = philo->meal_end;
	pthread_mutex_unlock(&philo->m_state);
	return (end);
}

static void	wait_meal_end(t_philo *philo)
{
	long	left;

	while (!get_stop(philo->data))
	{
		left = get_meal_end(philo) - get_time();
		if (left <= 0)
			break ;
		if (left > 3)
			usleep((left - 1) * 1000);
		else
			usleep(200);
	}
}

void	eat(t_philo *philo)
{
	wait_meal_end(philo);
	pthread_mutex_lock(&philo->m_state);
	philo->eaten_meals++;
	pthread_mutex_unlock(&philo->m_state);
}
