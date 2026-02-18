/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:09:57 by jihi              #+#    #+#             */
/*   Updated: 2026/02/18 18:29:32 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_sleep(t_data *data, long ts)
{
	long	start;

	start = get_time();
	while (!get_stop(data) && get_time() - start < ts)
		usleep(100);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	if (!ptr)
		return (NULL);
	philo = (t_philo *)ptr;
	while (!get_stop(philo->data))
	{
		if (take_forks(philo))
			break ;
		eat(philo);
		drop_forks(philo);
		print_state(philo->data, philo->id, SLEEP);
		my_sleep(philo->data, philo->data->t_to_sleep);
		print_state(philo->data, philo->id, THINK);
	}
	return (NULL);
}