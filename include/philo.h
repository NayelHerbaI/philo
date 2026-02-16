/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:29:57 by jihi              #+#    #+#             */
/*   Updated: 2026/02/16 18:35:15 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
// # include <stdio.h>

typedef struct s_data
{
	int	nb_philo;
	int	t_to_die;
	int	t_to_eat;
	int	t_to_think;
	int	nb_meals;
}	t_data;

// Utils

void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr(int nb);
int		ft_atoi(char *s);
int		ft_isdigits(char *s);

#endif