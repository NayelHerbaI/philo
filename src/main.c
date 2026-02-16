/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:29:05 by jihi              #+#    #+#             */
/*   Updated: 2026/02/16 18:41:44 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_handler(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 5 || ac != 6)
		return (0);
	while (i < ac)
	{
		if (!ft_isdigits(av[i]))
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (!error_handler(ac, av))
		return (-1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (-1);
	(void)ac;
	(void)av;
	return (0);
}
