/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:32:14 by debian            #+#    #+#             */
/*   Updated: 2024/07/23 15:44:49 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	int		i;
	
	philo = arg;
	i = 0;
	while (i < philo->meals || philo->meals == -1)
	{

		while (!*philo->left_fork || !philo->right_fork)
			(void)1;		
		eat(philo);

		// Dormir
		print_state(philo, SLEEPING);
		usleep(philo->data->time_to_sleep);

		// Penser
		print_state(philo, THINKING);

		if (philo->meals != -1)
			i++;
	}

	return (NULL);
}

bool	launch_processes(t_data *data, t_philo *philos)
{
	t_philo	*start;
	int		i;

	start = philos;
	// Create
	i = -1;
	while (i++, i < data->nb_philo)
	{
		philos->data = data;
		pthread_create(&philos->thread, NULL, routine, philos);
		philos = philos->next;
	}

	// Join
	philos = start;
	i = -1;
	while (i++, i < data->nb_philo)
	{
		// printf("join\n");
		pthread_join(philos->thread, NULL);
		philos = philos->next;
	}

	return (true);
}
