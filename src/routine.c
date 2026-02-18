/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:09:57 by jihi              #+#    #+#             */
/*   Updated: 2026/02/18 17:19:57 by jihi             ###   ########.fr       */
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
		print_state(philo->data, philo->id, "is thinking");
		my_sleep(philo->data, 1000);
	}
	return (NULL);
}