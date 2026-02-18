/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:29:05 by jihi              #+#    #+#             */
/*   Updated: 2026/02/18 17:32:32 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_int_min_max(int ac, char **av, int start)
{
	int	i;

	i = start;
	while (i < ac)
	{
		if (ft_atoi(av[i]) > 2147483647 || ft_atoi(av[i]) < -2147483648)
			return (1);
		i++;
	}
	return (0);
}

int	error_handler(int ac, char **av)
{
	int	i;

	i = 1;
	if ((ac != 5 && ac != 6) || check_int_min_max(ac, av, 1))
		return (1);
	while (i < ac)
	{
		if (ft_isdigits(av[i]) || !ft_atoi(av[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	clean_philos(t_data *data)
{
	int	i;

	i = 0;
	if (data->init.alloc_philos)
	{
		while (i < data->init.philos)
		{
			pthread_mutex_destroy(&data->philos[i].m_state);
			i++;
		}
		free(data->philos);
	}
}

void	clean_everything(t_data *data)
{
	int	i;

	i = 0;
	if (data->init.alloc_forks)
	{
		if (data->init.init_forks)
		{
			while (i < data->nb_philo)
			{
				pthread_mutex_destroy(&data->forks[i]);
				i++;
			}
		}
		free(data->forks);
	}
	if (data->init.m_print)
		pthread_mutex_destroy(&data->m_print);
	if (data->init.m_stop)
		pthread_mutex_destroy(&data->m_stop);
	clean_philos(data);
	if (data)
		free(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (error_handler(ac, av))
		return (ft_putstr("Input error\n", -1));
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr("Malloc error\n", -1));
	if (setup(ac, av, data))
		return (ft_putstr("Setup error\n", -1));
	if (start_threads(data))
		return (ft_putstr("Thread error\n", 1));
	my_sleep(data, 50);
	set_stop(data, 1);
	join_threads(data);
	clean_everything(data);
	return (0);
}
