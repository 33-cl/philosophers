/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:05:35 by debian            #+#    #+#             */
/*   Updated: 2024/07/09 16:05:57 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void free_philo_list(t_philo *head)
{
    if (!head)
        return;

    t_philo *current = head;
    do
    {
        t_philo *next = current->next;
        free(current);
        current = next;
    } while (current != head);
}