/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 02:00:00 by jihi              #+#    #+#             */
/*   Updated: 2026/05/23 02:00:00 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_sleep(t_data *data, long ms)
{
	long	end;
	long	left;

	end = get_time() + ms;
	while (!get_stop(data))
	{
		left = end - get_time();
		if (left <= 0)
			break ;
		if (left > 3)
			usleep((left - 1) * 1000);
		else
			usleep(500);
	}
}

void	safe_sleep(t_philo *philo, long ms)
{
	long	end;
	long	left;

	end = get_time() + ms;
	while (!get_stop(philo->data))
	{
		left = end - get_time();
		if (left <= 0)
			break ;
		touch_turn(philo);
		if (left > 3)
			usleep((left - 1) * 1000);
		else
			usleep(500);
	}
}
