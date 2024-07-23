#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# include <pthread.h>
# include <sys/time.h>

typedef enum    e_state
{
	TAKE_FORK,
	THINKING,
	EATING,
	SLEEPING,
	DEAD
} e_state;

typedef struct s_data
{
	int					time_at_start;
	int 				nb_philo;
	int 				time_to_die;
	int 				time_to_eat;
	int 				time_to_sleep;
	int			 		target;
	pthread_mutex_t		m_print;
	bool				print;
}	t_data;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*m_left_fork;
	pthread_mutex_t		m_right_fork;
	bool				*left_fork;
	bool				right_fork;
	int					meals;
	int					state;
	struct s_data		*data;
	struct s_philo		*prev;
	struct s_philo		*next;
}   t_philo;

// Initialisation
bool    init_data(t_data *data, t_philo **philos, int argc, char **argv);

// Execution
bool    launch_processes(t_data *data, t_philo *philos);
bool	eat(t_philo *philo);

// Utils
int		get_time(void);
void	print_state(t_philo *philo, int state);

// Free
void    free_philo_list(t_philo *head);

#endif