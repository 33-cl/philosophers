/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:49:10 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/23 15:44:32 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	eat(t_philo *philo)
{
	// Prendre les fourchettes
	pthread_mutex_lock(philo->m_left_fork);
	pthread_mutex_lock(&philo->m_right_fork);
	*philo->left_fork = false;
	philo->right_fork = false;
	pthread_mutex_unlock(philo->m_left_fork);
	pthread_mutex_unlock(&philo->m_right_fork);

	// Manger
	print_state(philo, EATING);
	usleep(philo->data->time_to_eat);

	// Rendre les fourchettes
	pthread_mutex_lock(philo->m_left_fork);
	pthread_mutex_lock(&philo->m_right_fork);
	*philo->left_fork = true;
	philo->right_fork = true;
	pthread_mutex_unlock(philo->m_left_fork);
	pthread_mutex_unlock(&philo->m_right_fork);
	
	return (true);
}