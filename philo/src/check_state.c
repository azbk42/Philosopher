/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emauduit <emauduit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:38:20 by emauduit          #+#    #+#             */
/*   Updated: 2024/04/09 16:20:15 by emauduit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int check_is_dead(t_philosophe *philo)
{
    pthread_mutex_lock(&philo->arg->is_dead_mutex);
    if (philo->arg->is_dead == true)
    {
        pthread_mutex_unlock(&philo->arg->is_dead_mutex);
        return (SUCCESS);
    }
    pthread_mutex_unlock(&philo->arg->is_dead_mutex);
    return (ERROR);
}

int check_nb_eat(t_philosophe *philo)
{
    if (philo->arg->nb_time_eat != 0)
    {
        pthread_mutex_lock(&philo->arg->state_eat_mutex);
        if (philo->arg->state_eat == true)
        {
            pthread_mutex_unlock(&philo->arg->state_eat_mutex);
            return (SUCCESS);
        }
        pthread_mutex_unlock(&philo->arg->state_eat_mutex);
    }
    return (ERROR);
}
