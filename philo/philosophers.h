/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:14:02 by maeferre          #+#    #+#             */
/*   Updated: 2024/08/28 20:39:22 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# include <pthread.h>
# include <sys/time.h>

typedef enum e_state
{
	TAKE_FORK,
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}	t_state;

typedef struct s_data
{
	int					time_at_start;
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					target;
	pthread_mutex_t		m_print;
	bool				print;
	pthread_mutex_t		m_stop;
	bool				stop;
}	t_data;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*m_left_fork;
	pthread_mutex_t		m_right_fork;
	bool				*left_fork;
	bool				right_fork;
	int					meals_to_eat;
	pthread_mutex_t		m_time_last_meal;
	int					time_last_meal;
	struct s_data		*data;
	struct s_philo		*prev;
	struct s_philo		*next;
}	t_philo;

// Init
bool	init_data(t_data *data, t_philo **philos, int argc, char **argv);

// Execution
bool	launch_processes(t_data *data, t_philo *philos);
bool	eat(t_philo *philo);
bool	think(t_philo *philo);
bool	sleeping(t_philo *philo);

// Utils
int		get_time(void);
bool	print_state(t_philo *philo, char *state);
bool	check_death(t_philo *philo);
void	ft_usleep(t_philo *philo, int sleep_time);
int		ft_atoi(const char *str);

// Free
void	free_data(t_philo *philo);
void	free_philos(t_philo *head);

#endif