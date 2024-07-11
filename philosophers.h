#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# include <pthread.h>

typedef enum    e_state
{
    THINKING,
	EATING,
    SLEEPING,
    DEAD
} e_state;

typedef struct s_data
{
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int target;
}   t_data;

typedef struct s_philo
{
    int             id;
    pthread_t       thread;
    bool            fork;
    int             meals_to_eat;
    int             state;
    struct s_philo  *previous;
    struct s_philo  *next;
}   t_philo;

// Initialisation
bool    init_data(t_data *data, t_philo **philos, int argc, char **argv);

// Free
void    free_philo_list(t_philo *head);

#endif