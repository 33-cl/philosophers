/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:49:10 by maeferre          #+#    #+#             */
/*   Updated: 2024/08/15 21:13:05 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	wait_n_take_forks(t_philo *philo);
static void	give_back_forks(t_philo *philo);

bool	eat(t_philo *philo)
{
	wait_n_take_forks(philo);
	if (check_death(philo))
		return (false);
	print_state(philo, EATING);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->m_time_last_meal);
	philo->time_last_meal = get_time() - philo->data->time_at_start;
	pthread_mutex_unlock(&philo->m_time_last_meal);
	give_back_forks(philo);
	return (true);
}

static bool	wait_n_take_forks(t_philo *philo)
{
	while (usleep(100), 1)
	{
		pthread_mutex_lock(philo->m_left_fork);
		if (*philo->left_fork)
		{
			*philo->left_fork = false;
			pthread_mutex_unlock(philo->m_left_fork);
			pthread_mutex_lock(&philo->m_right_fork);
			if (philo->right_fork)
			{
				philo->right_fork = false;
				pthread_mutex_unlock(&philo->m_right_fork);
				break ;
			}
			pthread_mutex_unlock(&philo->m_right_fork);
			pthread_mutex_lock(philo->m_left_fork);
			*philo->left_fork = true;
			pthread_mutex_unlock(philo->m_left_fork);
		}
		else
			pthread_mutex_unlock(philo->m_left_fork);
		if (check_death(philo))
			return (false);
	}
	return (true);
}

static void	give_back_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->m_left_fork);
	*philo->left_fork = true;
	pthread_mutex_unlock(philo->m_left_fork);
	pthread_mutex_lock(&philo->m_right_fork);
	philo->right_fork = true;
	pthread_mutex_unlock(&philo->m_right_fork);
}
