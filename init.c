/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:13:29 by debian            #+#    #+#             */
/*   Updated: 2024/08/15 21:12:56 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*create_philo(t_data *data, int id);
static t_philo	*init_philo_list(t_data *data);
static t_philo	*init_philo_forks(t_data *data, t_philo *philos);
static bool		philo_error(t_philo *philo, t_philo *head);

bool	init_data(t_data *data, t_philo **philos, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (false);
	pthread_mutex_init(&data->m_print, NULL);
	pthread_mutex_init(&data->m_stop, NULL);
	data->stop = 0;
	data->print = true;
	data->time_at_start = get_time();
	data->nb_philo = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		data->target = atoi(argv[5]);
	else
		data->target = -1;
	*philos = init_philo_list(data);
	if (!*philos)
		return (false);
	*philos = init_philo_forks(data, *philos);
	if (!*philos)
		return (false);
	return (true);
}

static t_philo	*init_philo_list(t_data *data)
{
	int		i;
	t_philo	*head;
	t_philo	*current;
	t_philo	*new_philo;

	if (data->nb_philo <= 0)
		return (NULL);
	head = create_philo(data, 0);
	if (!head)
		return (NULL);
	current = head;
	i = 0;
	while (i++, i < data->nb_philo)
	{
		new_philo = create_philo(data, i);
		if (!philo_error(new_philo, head))
			return (NULL);
		current->next = new_philo;
		new_philo->prev = current;
		current = new_philo;
	}
	current->next = head;
	head->prev = current;
	return (head);
}

static t_philo	*create_philo(t_data *data, int id)
{
	t_philo	*new_philo;

	new_philo = (t_philo *)malloc(sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	new_philo->time_last_meal = 0;
	new_philo->id = id;
	new_philo->thread = 0;
	new_philo->meals_to_eat = data->target;
	new_philo->right_fork = true;
	pthread_mutex_init(&new_philo->m_right_fork, NULL);
	pthread_mutex_init(&new_philo->m_time_last_meal, NULL);
	new_philo->prev = NULL;
	new_philo->next = NULL;
	return (new_philo);
}

static bool	philo_error(t_philo *philo, t_philo *head)
{
	t_philo	*temp;

	if (!philo)
	{
		while (head)
		{
			temp = head;
			head = head->next;
			free(temp);
		}
		return (false);
	}
	return (true);
}

static t_philo	*init_philo_forks(t_data *data, t_philo *philos)
{
	int		i;
	t_philo	*start;

	i = -1;
	start = philos;
	while (i++, i < data->nb_philo)
	{
		philos->m_left_fork = &(philos->prev->m_right_fork);
		philos->left_fork = &(philos->prev->right_fork);
		philos = philos->next;
	}
	return (start);
}
