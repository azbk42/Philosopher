/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emauduit <emauduit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:06:00 by azbk              #+#    #+#             */
/*   Updated: 2024/04/02 18:10:34 by emauduit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void *eat_routine(void *arg)
{
    t_philosophe *philo;

    philo = (t_philosophe *)arg;
    while (true)
    {
        printf("%d thinks %dms\n", philo->id, philo->arg->time_to_die);
        usleep(philo->arg->time_to_die * 1000);
        printf("\t\t%d is hungry\n", philo->id);
        pthread_mutex_lock(philo->fork_left);
        pthread_mutex_lock(philo->fork_right);
        printf("\t\t\t\t%d eats %dms\n", philo->id, philo->arg->time_to_eat);
        usleep(philo->arg->time_to_eat * 1000);
        pthread_mutex_unlock(philo->fork_right);
        pthread_mutex_unlock(philo->fork_left);
    }
}

void start_philosopher(t_data *data)
{
    int i;
    
    i = 0;
    while (i < data->arg->nb_philo)
    {
        pthread_create(&data->thread[i], NULL, eat_routine, &data->philosophe[i]);
        i++;
    }
    i = 0;
    while (i < data->arg->nb_philo)
    {
        pthread_join(data->thread[i], NULL);
        i++;
    }
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
        free_data(&data);
        return (ERROR_PHILO);
    }
    start_philosopher(&data);

    free_data(&data);
    return (0);
}
