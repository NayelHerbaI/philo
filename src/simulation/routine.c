/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:09:57 by jihi              #+#    #+#             */
/*   Updated: 2026/05/23 02:00:00 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_start(t_philo *philo)
{
	while (!get_stop(philo->data) && !get_ready(philo->data))
		usleep(500);
}

static int	routine_cycle(t_philo *philo, long *round)
{
	wait_turn(philo, *round);
	touch_turn(philo);
	if (*round > 0)
		print_state(philo->data, philo->id, THINK);
	if (take_forks(philo))
		return (1);
	if (!get_stop(philo->data))
		eat(philo);
	drop_forks(philo);
	(*round)++;
	if (get_stop(philo->data))
		return (1);
	print_state(philo->data, philo->id, SLEEP);
	safe_sleep(philo, philo->data->t_to_sleep);
	return (0);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	long	round;

	if (!ptr)
		return (NULL);
	philo = (t_philo *)ptr;
	round = 0;
	wait_start(philo);
	while (!get_stop(philo->data))
	{
		if (routine_cycle(philo, &round))
			break ;
	}
	return (NULL);
}
