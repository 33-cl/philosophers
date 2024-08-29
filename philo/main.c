/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:17:54 by debian            #+#    #+#             */
/*   Updated: 2024/08/28 20:09:52 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philos;

	if (!init_data(&data, &philos, argc, argv))
		return (printf("Invalid args\n"), 1);
	launch_processes(&data, philos);
	free_data(philos);
	return (0);
}
