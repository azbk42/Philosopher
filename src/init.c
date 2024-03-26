/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azbk <azbk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:48:59 by azbk              #+#    #+#             */
/*   Updated: 2024/03/05 11:01:54 by azbk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int init_philo(t_philo *philo, char **av)
{
    if (parsing_arg(av) == ERROR)
    {
        printf("Error: wrong arguments\nYou should have only number and positive number\n");
        return (ERROR_ARGS);
    }
    philo->nb_philo = ft_atoi(av[1]);
    philo->time_to_die = ft_atoi(av[2]);
    philo->time_to_eat = ft_atoi(av[3]);
    philo->time_to_sleep = ft_atoi(av[4]);
    if (av[5])
        philo->nb_time_eat = ft_atoi(av[5]);
    else
        philo->nb_time_eat = 0;
    if (philo->nb_philo == -1 || philo->time_to_die == -1 || philo->time_to_eat == -1
        || philo->time_to_sleep == -1 || philo->nb_time_eat == -1)
    {
        printf("Error: should be INT_MAX or less");
        return (ERROR);
    }
    if (philo->nb_philo > 200)
    {
        printf("Erorr: number of philosopher must be 200 or less\n");
        return (ERROR);
    }
    return (SUCCESS);
}
