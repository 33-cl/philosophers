/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:28:24 by maeferre          #+#    #+#             */
/*   Updated: 2024/08/15 21:18:47 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_stop);
	if (philo->data->stop)
		return (pthread_mutex_unlock(&philo->data->m_stop), true);
	pthread_mutex_unlock(&philo->data->m_stop);
	return (false);
}

int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_state(t_philo *philo, int state)
{
	int	timestamp_in_ms;

	timestamp_in_ms = get_time() - philo->data->time_at_start;
	pthread_mutex_lock(&philo->data->m_print);
	printf("%d %d ", timestamp_in_ms, philo->id + 1);
	if (state == TAKE_FORK)
		printf("has taken a fork\n");
	else if (state == EATING)
		printf("is eating\n");
	else if (state == SLEEPING)
		printf("is sleeping\n");
	else if (state == THINKING)
		printf("is thinking\n");
	else if (state == DEAD)
		printf("died\n");
	pthread_mutex_unlock(&philo->data->m_print);
}
