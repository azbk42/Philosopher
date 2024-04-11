/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emauduit <emauduit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:48:32 by emauduit          #+#    #+#             */
/*   Updated: 2024/04/11 19:43:35 by emauduit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int check_state_death(t_data *data, int i)
{
    unsigned long time;
    
    pthread_mutex_lock(&data->arg->last_eat_mutex);
    time = get_time_diff(data->philosophe[i].last_eat);
    pthread_mutex_unlock(&data->arg->last_eat_mutex);
    if (time > (unsigned long)data->arg->time_to_die)
    {
        printf(BLACK"%lu %d is dead"RESET_COLOR"\n", time, i+1);
        pthread_mutex_lock(&data->arg->is_dead_mutex);
        data->arg->is_dead = true;
        pthread_mutex_unlock(&data->arg->is_dead_mutex);
        return (SUCCESS);
    }
    return (ERROR);
}

void *monitor_die(void *arg)
{
    t_data *data;
    int i;

    data = (t_data *)arg;
    while (true)
    {
        i = 0;
        if (data->arg->nb_time_eat != 0)
        {
            if (check_nb_eat(data->philosophe) == SUCCESS)
                return (NULL);
        }
        while (i < data->arg->nb_philo)
        {
            if (check_state_death(data, i) == SUCCESS)
                return (NULL);
            i++;
        }
    }
    return (NULL);
}

void monitor_nb_eat(t_data *data)
{
    int i;
    
    while (data->arg->is_dead == false && data->arg->state_eat == false)
    {
        i = 0;
        while (i < data->arg->nb_philo)
        {
            pthread_mutex_lock(&data->arg->nb_eat_mutex);
            if (data->philosophe[i].nb_eat < data->arg->nb_time_eat)
            {
                pthread_mutex_unlock(&data->arg->nb_eat_mutex);
                break;
            }
            pthread_mutex_unlock(&data->arg->nb_eat_mutex);
            i++;
            
        }
        if (i == data->arg->nb_philo)
        {
            pthread_mutex_lock(&data->arg->state_eat_mutex);
            data->arg->state_eat = true;
            pthread_mutex_unlock(&data->arg->state_eat_mutex);
            return ;
        }    
    }
}
