/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:32:14 by debian            #+#    #+#             */
/*   Updated: 2024/08/15 21:18:32 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg);
void	*monitor(void *arg);

bool	launch_processes(t_data *data, t_philo *philos)
{
	pthread_t	monitor_thread;
	t_philo		*start;
	int			i;

	start = philos;
	i = -1;
	while (i++, i < data->nb_philo)
	{
		philos->data = data;
		pthread_create(&philos->thread, NULL, routine, philos);
		philos = philos->next;
	}
	pthread_create(&monitor_thread, NULL, monitor, philos);
	philos = start;
	i = -1;
	while (i++, i < data->nb_philo)
	{
		pthread_join(philos->thread, NULL);
		philos = philos->next;
	}
	pthread_join(monitor_thread, NULL);
	return (true);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = arg;
	i = 0;
	while (i < philo->meals_to_eat || philo->meals_to_eat == -1)
	{
		if (!eat(philo))
			return (NULL);
		if (!sleeping(philo))
			return (NULL);
		if (!think(philo))
			return (NULL);
		if (philo->meals_to_eat != -1)
			i++;
		usleep(100);
	}
	pthread_mutex_lock(&philo->data->m_stop);
	philo->data->stop = 1;
	pthread_mutex_unlock(&philo->data->m_stop);
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		time_since_eat;

	philo = arg;
	data = philo->data;
	while (1)
	{
		pthread_mutex_lock(&philo->m_time_last_meal);
		time_since_eat = (get_time() - data->time_at_start)
			- philo->time_last_meal > data->time_to_die;
		pthread_mutex_unlock(&philo->m_time_last_meal);
		if (time_since_eat)
		{
			if (check_death(philo))
				return (NULL);
			print_state(philo, DEAD);
			pthread_mutex_lock(&philo->data->m_stop);
			philo->data->stop = 1;
			pthread_mutex_unlock(&philo->data->m_stop);
			return (NULL);
		}
		philo = philo->next;
	}
	return (NULL);
}
