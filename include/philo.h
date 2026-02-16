/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:29:57 by jihi              #+#    #+#             */
/*   Updated: 2026/02/16 19:28:09 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_data
{
	long	nb_philo;
	long	t_to_die;
	long	t_to_eat;
	long	t_to_sleep;
	long	nb_meals;
}	t_data;

// Utils

void	ft_putchar(char c);
int		ft_putstr(char *str, int return_value);
void	ft_putnbr(int nb);
long	ft_atoi(char *s);
int		ft_isdigits(char *s);

// Setup

int		setup(int ac, char **av, t_data *data);

#endif