/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:13:29 by debian            #+#    #+#             */
/*   Updated: 2024/07/09 16:28:51 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo *create_philo(t_data *data, int id)
{
    t_philo *new_philo;

    new_philo = (t_philo *)malloc(sizeof(t_philo));
    if (!new_philo)
        return (NULL);
    new_philo->id = id;
    new_philo->thread = 0;
    new_philo->fork = false;
    new_philo->meals_to_eat = data->target;
    new_philo->state = THINKING;
    new_philo->previous = NULL;
    new_philo->next = NULL;
    return (new_philo);
}

t_philo *init_philo_list(t_data *data)
{
    int i;
    t_philo *head;
    t_philo *current;
    t_philo *new_philo;
    t_philo *temp;

    if (data->nb_philo <= 0)
        return (NULL);
    head = create_philo(data, 1);
    if (!head)
        return (NULL);
    current = head;
    i = 1;
    while (i++, i < data->nb_philo)
    {
        new_philo = create_philo(data, i);
        if (!new_philo)
        {
            while (head)
            {
                temp = head;
                head = head->next;
                free(temp);
            }
            return (NULL);
        }
        current->next = new_philo;
        new_philo->previous = current;
        current = new_philo;
    }
    current->next = head;
    head->previous = current;
    return (head);
}

bool    init_data(t_data *data, t_philo **philos, int argc, char **argv)
{
    if (argc < 5 || argc > 6)
        return (false);
    
    data->nb_philo = atoi(argv[1]);
    data->time_to_die = atoi(argv[2]);
    data->time_to_eat = atoi(argv[3]);
    data->time_to_sleep = atoi(argv[4]);
    if (argc == 6)
        data->target = atoi(argv[5]);
    else
        data->target = -1;

    *philos = init_philo_list(data);
    if (!*philos)
        return (false);
    return (true);
}
