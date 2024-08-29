/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:28:24 by maeferre          #+#    #+#             */
/*   Updated: 2024/08/29 14:56:01 by maeferre         ###   ########.fr       */
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

bool	print_state(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->data->m_stop);
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->m_stop);
		return (false);
	}
	printf("%d %d %s", get_time() - philo->data->time_at_start,
		philo->id + 1, state);
	pthread_mutex_unlock(&philo->data->m_stop);
	return (true);
}

void	ft_usleep(t_philo *philo, int sleep_time)
{
	int	goal;

	goal = get_time() + sleep_time;
	while (get_time() < goal)
	{
		if (check_death(philo))
			break ;
		usleep(100);
	}
}

int	ft_atoi(const char *str)
{
	int	neg;
	int	i;
	int	num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (-1);
		i++;
	}
	i = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (i == 6)
			return (-1);
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}
