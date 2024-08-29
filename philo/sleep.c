/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 20:37:39 by maeferre          #+#    #+#             */
/*   Updated: 2024/08/27 17:28:50 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	sleeping(t_philo *philo)
{
	if (!print_state(philo, "is sleeping\n"))
		return (false);
	ft_usleep(philo, philo->data->time_to_sleep);
	return (true);
}
