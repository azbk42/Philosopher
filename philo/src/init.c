/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emauduit <emauduit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:48:59 by azbk              #+#    #+#             */
/*   Updated: 2024/04/09 15:06:18 by emauduit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	fill_arg(t_argument *arg, char **av)
{
	arg->nb_philo = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		arg->nb_time_eat = ft_atoi(av[5]);
	else
		arg->nb_time_eat = 0;
    arg->is_dead = false;
    arg->state_eat = false;
    if (pthread_mutex_init(&arg->is_dead_mutex, NULL) != 0)
    {
        write(2, "Error: mutex init is_dead_mutex failed\n", 40);
        return (ERROR); 
    }
    if (av[5])
    {
        if (pthread_mutex_init(&arg->state_eat_mutex, NULL) != 0)
        {
            write(2, "Error: mutex init state_eat_mutex failed\n", 42);
            return (ERROR); 
        }
    }
    return (SUCCESS);
}

int	init_arg(t_argument *arg, char **av)
{
	if (parsing_arg(av) == ERROR)
	{
		write(2, "Error: wrong arguments\n", 24);
		write(2, "You should have only number and positive number\n", 51);
		return (ERROR_ARGS);
	}
	if (fill_arg(arg, av) == ERROR)
        return (ERROR);
	if (arg->nb_philo == -1 || arg->time_to_die == -1
		|| arg->time_to_eat == -1 || arg->time_to_sleep == -1
		|| arg->nb_time_eat == -1)
	{
		write(2, "Error: should be INT_MAX or less and 0 or more\n", 48);
		return (ERROR);
	}
	if (arg->nb_philo > 200 || arg->nb_philo < 1)
	{
		write(2, "Erorr: number of philosopher, less than 200 and more than 1\n", 60);
		return (ERROR);
	}
	return (SUCCESS);
}
int init_data(t_argument *arg, t_data *data)
{
    int i;

    data->arg = arg;
    data->thread = malloc(sizeof(pthread_t) * arg->nb_philo);
    if (!data->thread)
    {
        write(2, "Error: malloc failed: data->thread\n", 22);
        return (ERROR);
    }
    data->forks = malloc(sizeof(pthread_mutex_t) * arg->nb_philo);
    if (!data->forks)
    {
        return (free_error_init(data->thread, NULL , -1));
    }
    i = 0;
    while (i < arg->nb_philo)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
        {
            return (free_error_init(data->thread, data->forks, i));
        }
        i++;
    }
    return (SUCCESS);
}
static void fill_philo(t_data *data, int i)
{
    data->philosophe[i].nb_eat = 0;
    data->philosophe[i].id = i+1;
    data->philosophe[i].arg = data->arg;
    if (i == data->arg->nb_philo -1)
    {
        data->philosophe[i].fork_right = &data->forks[0];
        data->philosophe[i].fork_left = &data->forks[i];
    }
    else
    {
        data->philosophe[i].fork_right = &data->forks[i];
        data->philosophe[i].fork_left = &data->forks[i + 1];
    }
    if (i == data->arg->nb_philo -1)
    {
        data->philosophe[i].fork_left_id = 1;
        data->philosophe[i].fork_right_id = i+1;
    }
    else
    {
        data->philosophe[i].fork_left_id = i+2;
        data->philosophe[i].fork_right_id = i +1;
    }
}

int init_philo(t_data *data)
{
    int i;

    i = 0;
    data->philosophe = malloc(sizeof(t_philosophe) * data->arg->nb_philo);
    if (!data->philosophe)
    {
        free_data(data);
        write(2, "Error: malloc failed: data->philosophe\n", 22);
        return (ERROR);
    }
    while (i < data->arg->nb_philo)
    {
        fill_philo(data, i);
        i++;
    }
    return (SUCCESS);
}
