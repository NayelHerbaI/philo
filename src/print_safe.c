/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_safe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:05:13 by jihi              #+#    #+#             */
/*   Updated: 2026/02/17 11:37:06 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(long time, int id, char *msg)
{
	ft_putnbr(time);
	ft_putchar(' ');
	ft_putnbr(id);
	ft_putchar(' ');
	ft_putstr(msg, 0);
	ft_putchar('\n');
}

void	print_death(t_data *data, int id)
{
	pthread_mutex_lock(&data->m_print);
	print_message(elapsed_time(data), id, "died");
	pthread_mutex_unlock(&data->m_print);
}

void	print_state(t_data *data, int id, char *msg)
{
	pthread_mutex_lock(&data->m_print);
	if (!get_stop(data))
		print_message(elapsed_time(data), id, msg);
	pthread_mutex_unlock(&data->m_print);
}
