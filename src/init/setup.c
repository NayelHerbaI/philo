/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:51:30 by jihi              #+#    #+#             */
/*   Updated: 2026/05/23 02:00:00 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	setup_vars(int ac, char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	data->t_to_die = ft_atoi(av[2]);
	data->t_to_eat = ft_atoi(av[3]);
	data->t_to_sleep = ft_atoi(av[4]);
	data->nb_meals = -1;
	if (ac == 6)
		data->nb_meals = ft_atoi(av[5]);
	data->timers.start = 0;
	data->stop = 0;
	data->ready = 0;
	data->init = (t_init){0, 0, 0, 0, 0, 0, 0, 0, 0};
}

static int	setup_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->m_stop, NULL))
		return (1);
	data->init.m_stop = 1;
	if (pthread_mutex_init(&data->m_print, NULL))
		return (1);
	data->init.m_print = 1;
	if (pthread_mutex_init(&data->m_table, NULL))
		return (1);
	data->init.m_table = 1;
	return (0);
}

int	setup(int ac, char **av, t_data *data)
{
	setup_vars(ac, av, data);
	if (setup_mutexes(data) || setup_forks(data) || setup_philos(data))
	{
		clean_everything(data);
		return (1);
	}
	return (0);
}
