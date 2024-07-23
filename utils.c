/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:28:24 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/23 15:52:30 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec);
}

void	print_state(t_philo *philo, int state)
{
	int	timestamp_in_ms;

	printf("print = %d\n", philo->data->print);
	while (philo->data->print == false)
		printf("print = %d\n", philo->data->print);

	pthread_mutex_lock(&philo->data->m_print);
	philo->data->print = false;
	pthread_mutex_unlock(&philo->data->m_print);
	timestamp_in_ms = get_time() - philo->data->time_at_start;
	printf("%d %d is ", timestamp_in_ms,philo->id);
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
	pthread_mutex_lock(&philo->data->m_print);
	philo->data->print = true;
	pthread_mutex_unlock(&philo->data->m_print);
}

