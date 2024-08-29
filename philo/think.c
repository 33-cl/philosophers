/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 20:32:22 by maeferre          #+#    #+#             */
/*   Updated: 2024/08/27 17:28:42 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	think(t_philo *philo)
{
	int		time_left;
	t_data	*data;

	data = philo->data;
	if (data->nb_philo % 2 != 0)
	{
		pthread_mutex_lock(&philo->m_time_last_meal);
		time_left = get_time() - data->time_at_start - philo->time_last_meal;
		pthread_mutex_unlock(&philo->m_time_last_meal);
		if (time_left / 2 > 0)
			ft_usleep(philo, (time_left / 2));
	}
	if (!print_state(philo, "is thinking\n"))
		return (false);
	return (true);
}
