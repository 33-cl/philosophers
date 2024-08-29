/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:49:10 by maeferre          #+#    #+#             */
/*   Updated: 2024/08/29 17:10:59 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	wait_n_take_forks(t_philo *philo);
static void	give_back_forks(t_philo *philo);
static bool	have_two_forks(t_philo *philo);
static bool	take_fork(t_philo *philo, pthread_mutex_t *mutex, bool *fork);

bool	eat(t_philo *philo)
{
	long long	current_time;

	if (!wait_n_take_forks(philo))
		return (false);
	if (!print_state(philo, "is eating\n"))
	{
		give_back_forks(philo);
		return (false);
	}
	current_time = get_time() - philo->data->time_at_start;
	pthread_mutex_lock(&philo->m_time_last_meal);
	philo->time_last_meal = current_time;
	pthread_mutex_unlock(&philo->m_time_last_meal);
	ft_usleep(philo, philo->data->time_to_eat);
	give_back_forks(philo);
	return (true);
}

static bool	wait_n_take_forks(t_philo *philo)
{
	while (1)
	{
		if (have_two_forks(philo))
			break ;
		if (!take_fork(philo, philo->m_left_fork, philo->left_fork))
			return (false);
		if (!take_fork(philo, &philo->m_right_fork, &philo->right_fork))
			return (false);
		if (check_death(philo))
			return (false);
		usleep(100);
	}
	if (check_death(philo))
		return (false);
	return (true);
}

static bool	have_two_forks(t_philo *philo)
{
	if (philo->m_left_fork < &philo->m_right_fork)
	{
		pthread_mutex_lock(philo->m_left_fork);
		pthread_mutex_lock(&philo->m_right_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->m_right_fork);
		pthread_mutex_lock(philo->m_left_fork);
	}
	if (!*philo->left_fork && !philo->right_fork)
	{
		pthread_mutex_unlock(&philo->m_right_fork);
		pthread_mutex_unlock(philo->m_left_fork);
		return (true);
	}
	pthread_mutex_unlock(&philo->m_right_fork);
	pthread_mutex_unlock(philo->m_left_fork);
	return (false);
}

static bool	take_fork(t_philo *philo, pthread_mutex_t *mutex, bool *fork)
{
	pthread_mutex_lock(mutex);
	if (*fork)
	{
		*fork = false;
		if (!print_state(philo, "has taken a fork\n"))
			return (false);
	}
	pthread_mutex_unlock(mutex);
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
