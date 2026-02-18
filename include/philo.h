/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:29:57 by jihi              #+#    #+#             */
/*   Updated: 2026/02/18 18:22:16 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

#define EAT "is eating"
#define SLEEP "is sleeping"
#define THINK "is thinking"
#define TAKE_FORK "has taken a fork"

// ----------------  Structs ------------------

typedef struct s_philo	t_philo;

typedef struct s_timers
{
	long	start;
}	t_timers;

typedef struct s_init
{
	int	alloc_forks;
	int	init_forks;
	int	m_stop;
	int	m_print;
	int	alloc_philos;
	int	philos;
}	t_init;

typedef struct s_data
{
	long			nb_philo;
	long			t_to_die;
	long			t_to_eat;
	long			t_to_sleep;
	long			nb_meals;
	int				stop;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_print;
	pthread_mutex_t	*forks;
	t_timers		timers;
	t_init			init;
	t_philo			*philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	long			eaten_meals;
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	m_state;
	t_data			*data;
}	t_philo;

// ---------------- Utils ------------------

void	ft_putchar(char c);
int		ft_putstr(char *str, int return_value);
void	ft_putnbr(long nb);
long	ft_atoi(char *s);
int		ft_isdigits(char *s);
void	clean_everything(t_data *data);
void	print_state(t_data *data, int id, char *msg);

// ---------------- Time ------------------

long	get_time(void);
long	elapsed_time(t_data *data);
void	my_sleep(t_data *data, long ts);

// ---------------- Stop ------------------

void	set_stop(t_data *data, int v);
int		get_stop(t_data *data);

// ---------------- Setup ------------------

int		setup(int ac, char **av, t_data *data);

// ---------------- Thread ------------------

int		start_threads(t_data *data);
int		join_threads(t_data *data);

// ---------------- Routine ------------------

void	*philo_routine(void *ptr);

// ---------------- Forks ------------------

int		take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);

// ---------------- Eat -------------------

void	eat(t_philo *philo);

#endif