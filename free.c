/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:05:35 by debian            #+#    #+#             */
/*   Updated: 2024/08/15 21:12:07 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_data(t_philo *philo)
{
	pthread_mutex_destroy(&philo->data->m_print);
	pthread_mutex_destroy(&philo->data->m_stop);
	free_philos(philo);
}

void	free_philos(t_philo *head)
{
	t_philo	*current;
	t_philo	*next;

	if (!head)
		return ;
	current = head;
	next = current->next;
	while (current != head || next != head)
	{
		next = current->next;
		pthread_mutex_destroy(&current->m_right_fork);
		pthread_mutex_destroy(&current->m_time_last_meal);
		free(current);
		current = NULL;
		current = next;
	}
}
