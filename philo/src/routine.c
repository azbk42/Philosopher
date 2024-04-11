/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emauduit <emauduit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:08:16 by emauduit          #+#    #+#             */
/*   Updated: 2024/04/11 18:45:09 by emauduit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	*eat_routine(void *arg)
{
	t_philosophe	*philo;

	philo = (t_philosophe *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->arg->time_to_eat - 10);
	while (true)
	{
		if (check_nb_eat(philo) == SUCCESS)
			break ;
		if (check_is_dead(philo) == SUCCESS)
			break ;
		if (ft_fork_right(philo) == ERROR)
			break ;
		if (ft_fork_left(philo) == ERROR)
			break ;
		ft_is_eating(philo);
		ft_is_spleeping(philo);
		if (check_is_dead(philo) == SUCCESS)
			break ;
		ft_is_thinking(philo);
	}
	return (NULL);
}
