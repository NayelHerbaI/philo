/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:29:05 by jihi              #+#    #+#             */
/*   Updated: 2026/05/23 02:00:00 by jihi             ###   ########.fr       */
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

static int	error_handler(int ac, char **av)
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

int	main(int ac, char **av)
{
	t_data	*data;

	if (error_handler(ac, av))
		return (ft_putstr("Input error\n", 1));
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr("Malloc error\n", 1));
	if (setup(ac, av, data))
		return (ft_putstr("Setup error\n", 1));
	if (start_threads(data))
	{
		join_threads(data);
		clean_everything(data);
		return (ft_putstr("Thread error\n", 1));
	}
	monitor(data);
	join_threads(data);
	clean_everything(data);
	return (0);
}
