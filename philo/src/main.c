/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emauduit <emauduit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:06:00 by azbk              #+#    #+#             */
/*   Updated: 2024/04/11 18:49:30 by emauduit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void start_philosopher(t_data *data)
{
    int i;
    
    i = 0;
    while (i < data->arg->nb_philo)
    {
        data->philosophe[i].last_eat = get_time();
        pthread_create(&data->thread[i], NULL, eat_routine, &data->philosophe[i]);
        i++;
    }
    i = 0;
    pthread_create(&data->check_die, NULL, monitor_die, data);
    if (data->arg->nb_time_eat != 0)
    {
        monitor_nb_eat(data);
    }
    while (i < data->arg->nb_philo)
    {
        pthread_join(data->thread[i], NULL);
        i++;
    }
    pthread_join(data->check_die, NULL);
}

int main(int ac, char **av)
{
    t_argument arg;
    t_data data;
    
    if (ac != 5 && ac != 6)
    {
        write(2, "Error: wrong number of arguments\n", 34);
        return (ERROR_ARGS);
    }
    if (init_arg(&arg, av) == ERROR)
        return (ERROR_INIT_ARGS);
    if (init_data(&arg, &data) == ERROR)
        return (ERROR_DATA);
    if (init_philo(&data) == ERROR)
    {
        return (ERROR_PHILO);
    }
    start_philosopher(&data);
    free_data(&data);
    return (0);
}
