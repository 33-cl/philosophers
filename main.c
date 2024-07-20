/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:17:54 by debian            #+#    #+#             */
/*   Updated: 2024/07/21 00:52:20 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void print_philo(t_philo *head);

/*
	./philosophers nb_philo ttdie tteat ttsleep number_of_times_a_philo_must_eat
*/

int main(int argc, char **argv)
{
	t_data      data;
	t_philo     *philos;

	if (!init_data(&data, &philos, argc, argv))
		return (printf("Invalid args\n"), 1);
	print_philo(philos);
	launch_processes(data, philos);
	// if (!launch_processes(data, philos))
	//     return (free_data(philos), 1);
	// free_data(philos);
	return (0);
}


void print_philo(t_philo *head)
{
	if (!head)
	{
		printf("The list is empty.\n");
		return;
	}

	t_philo *current = head;
	do
	{
		printf("Philosopher %d\n", current->id);
		printf("  Left  fork = %p\n", current->left_fork);
		printf("  Right fork = %p\n", &current->right_fork);
		printf("  Number of Meals to eat: %d\n", current->meals_to_eat);
		printf("  State: %d\n", current->state);
		printf("  Previous Philosopher: %d\n", current->prev ? current->prev->id : -1);
		printf("  Next Philosopher: %d\n\n", current->next ? current->next->id : -1);
		current = current->next;
	} while (current != head);
}