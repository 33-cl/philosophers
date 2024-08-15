/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 20:37:39 by maeferre          #+#    #+#             */
/*   Updated: 2024/08/15 20:47:39 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	sleeping(t_philo *philo)
{
	if (check_death(philo))
		return (false);
	print_state(philo, SLEEPING);
	usleep(philo->data->time_to_sleep * 1000);
	return (true);
}
