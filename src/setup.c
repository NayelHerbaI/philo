/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:51:30 by jihi              #+#    #+#             */
/*   Updated: 2026/02/17 11:13:10 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	setup_vars(int ac, char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	data->t_to_die = ft_atoi(av[2]);
	data->t_to_eat = ft_atoi(av[3]);
	data->t_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_meals = ft_atoi(av[5]);
	else
		data->nb_meals = -1;
	data->timers.start = get_time();
	data->stop = 0;
}

static int	setup_threads_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->m_stop, NULL))
		return (1);
	if (pthread_mutex_init(&data->m_print, NULL))
		return (1);
	return (0);
}

int	setup(int ac, char **av, t_data *data)
{
	setup_vars(ac, av, data);
	if (setup_threads_mutexes(data))
		return (1);
	return (0);
}
