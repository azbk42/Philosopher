/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azbk <azbk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:06:00 by azbk              #+#    #+#             */
/*   Updated: 2024/03/06 11:47:38 by azbk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"


void start_philosopher(t_philo *philo)
{
    
}


int main(int ac, char **av)
{
    t_philo philo;
    
    philo.nb_philo = 0;
    philo.nb_time_eat = 0;
    philo.time_to_die = 0;
    philo.time_to_eat = 0;
    philo.time_to_sleep = 0;
    if (ac != 5 && ac != 6)
    {
        printf("Error: wrong number of arguments\n");
        return (ERROR_ARGS);
    }
    if (init_philo(&philo, av) == ERROR)
        return (ERROR);
    start_philosopher(&philo);
    
    return (0);
}