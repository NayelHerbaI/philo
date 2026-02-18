/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:51:30 by jihi              #+#    #+#             */
/*   Updated: 2026/02/18 17:05:02 by jihi             ###   ########.fr       */
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
	data->init.alloc_forks = 0;
	data->init.init_forks = 0;
	data->init.m_print = 0;
	data->init.m_stop = 0;
	data->init.philos = 0;
	data->init.alloc_philos = 0;
}

static int	failed_forks(t_data *data, long init)
{
	long	i;

	i = 0;
	while (i < init)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	return (1);
}

static int	setup_forks_print_stop(t_data *data)
{
	long	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	data->init.alloc_forks = 1;
	if (pthread_mutex_init(&data->m_stop, NULL))
		return (1);
	data->init.m_stop = 1;
	if (pthread_mutex_init(&data->m_print, NULL))
		return (1);
	data->init.m_print = 1;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (failed_forks(data, i));
		i++;
	}
	data->init.init_forks = 1;
	return (0);
}

static int	setup_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (1);
	data->init.philos = 0;
	data->init.alloc_philos = 1;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal = data->timers.start;
		data->philos[i].eaten_meals = 0;
		data->philos[i].data = data;
		data->philos[i].left = &data->forks[i];
		data->philos[i].right = &data->forks[(i + 1) % data->nb_philo];
		if (pthread_mutex_init(&data->philos[i].m_state, NULL))
			return (1);
		data->init.philos++;
		i++;
	}
	return (0);
}

int	setup(int ac, char **av, t_data *data)
{
	setup_vars(ac, av, data);
	if (setup_forks_print_stop(data))
	{
		clean_everything(data);
		return (1);
	}
	if (setup_philos(data))
	{
		clean_everything(data);
		return (1);
	}
	return (0);
}
