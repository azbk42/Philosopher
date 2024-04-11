/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emauduit <emauduit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:00:52 by emauduit          #+#    #+#             */
/*   Updated: 2024/04/11 17:40:39 by emauduit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	fill_arg(t_argument *arg, char **av)
{
	arg->nb_philo = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		arg->nb_time_eat = ft_atoi(av[5]);
	}
	else
		arg->nb_time_eat = 0;
	arg->is_dead = false;
	arg->state_eat = false;
	return (SUCCESS);
}
void	fill_philo(t_data *data, int i)
{
	data->philosophe[i].nb_eat = 0;
	data->philosophe[i].id = i + 1;
	data->philosophe[i].arg = data->arg;
	if (i == data->arg->nb_philo - 1)
	{
		data->philosophe[i].fork_right = &data->forks[0];
		data->philosophe[i].fork_left = &data->forks[i];
	}
	else
	{
		data->philosophe[i].fork_right = &data->forks[i];
		data->philosophe[i].fork_left = &data->forks[i + 1];
	}
	if (i == data->arg->nb_philo - 1)
	{
		data->philosophe[i].fork_left_id = 1;
		data->philosophe[i].fork_right_id = i + 1;
	}
	else
	{
		data->philosophe[i].fork_left_id = i + 2;
		data->philosophe[i].fork_right_id = i + 1;
	}
}
