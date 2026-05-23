/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:29:57 by jihi              #+#    #+#             */
/*   Updated: 2026/05/23 02:00:00 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define TAKE_FORK "has taken a fork"

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
	int	m_table;
	int	alloc_busy;
	int	alloc_philos;
	int	philos;
	int	threads;
}	t_init;

typedef struct s_data
{
	long			nb_philo;
	long			t_to_die;
	long			t_to_eat;
	long			t_to_sleep;
	long			nb_meals;
	int				stop;
	int				ready;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_table;
	pthread_mutex_t	*forks;
	int				*fork_busy;
	t_timers		timers;
	t_init			init;
	t_philo			*philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	long			meal_end;
	long			eaten_meals;
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	int				left_i;
	int				right_i;
	pthread_mutex_t	m_state;
	t_data			*data;
}	t_philo;

void	ft_putchar(char c);
int		ft_putstr(char *str, int return_value);
void	ft_putnbr(long nb);
long	ft_atoi(char *s);
int		ft_isdigits(char *s);

void	clean_everything(t_data *data);
int		setup(int ac, char **av, t_data *data);
int		setup_forks(t_data *data);
int		setup_philos(t_data *data);

long	get_time(void);
long	elapsed_time(t_data *data);
void	my_sleep(t_data *data, long ms);

void	print_state(t_data *data, int id, char *msg);
void	print_death(t_data *data, int id);

void	set_stop(t_data *data, int v);
int		get_stop(t_data *data);
void	set_ready(t_data *data, int v);
int		get_ready(t_data *data);
void	monitor(t_data *data);

int		start_threads(t_data *data);
int		join_threads(t_data *data);
void	*philo_routine(void *ptr);

int		take_forks(t_philo *philo);
int		wait_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
void	eat(t_philo *philo);

long	get_period(t_data *data);
void	wait_turn(t_philo *philo, long round);
void	touch_turn(t_philo *philo);
void	safe_sleep(t_philo *philo, long ms);

#endif
