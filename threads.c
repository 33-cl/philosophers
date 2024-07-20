/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:32:14 by debian            #+#    #+#             */
/*   Updated: 2024/07/21 00:59:34 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	(void)arg;
	printf("launched\n");
	return (NULL);
}

bool	launch_processes(t_data data, t_philo *philos)
{
	t_philo	*start;
	int		i;

	start = philos;

	// Create
	i = -1;
	while (i++, i < data.nb_philo)
	{
		pthread_create(&philos->thread, NULL, routine, NULL);
		philos = philos->next;
	}

	// Join
	philos = start;
	i = -1;
	while (i++, i < data.nb_philo)
	{
		printf("join\n");
		pthread_join(philos->thread, NULL);
		philos = philos->next;
	}

	return (true);
}
