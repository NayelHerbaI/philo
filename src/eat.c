/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:17:30 by jihi              #+#    #+#             */
/*   Updated: 2026/02/18 18:23:31 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_state);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->m_state);
	print_state(philo->data, philo->id, EAT);
	my_sleep(philo->data, philo->data->t_to_eat);
	pthread_mutex_lock(&philo->m_state);
	philo->eaten_meals++;
	pthread_mutex_unlock(&philo->m_state);
}