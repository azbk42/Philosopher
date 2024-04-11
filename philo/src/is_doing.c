/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_doing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emauduit <emauduit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:42:03 by emauduit          #+#    #+#             */
/*   Updated: 2024/04/11 19:41:25 by emauduit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int ft_fork_right(t_philosophe *philo)
{
    pthread_mutex_lock(philo->fork_right);
    if (philo->arg->nb_philo == 1)
    {
        ft_usleep(philo->arg->time_to_die);
    }
    if (check_is_dead(philo) == SUCCESS)
    {
        pthread_mutex_unlock(philo->fork_right);
        return (ERROR);
    }
    pthread_mutex_lock(&philo->arg->last_eat_mutex);
    printf(YELLOW "\t\t\t%ld %d has taken a fork"RESET_COLOR"\n", get_time_diff(philo->last_eat),philo->id);
    pthread_mutex_unlock(&philo->arg->last_eat_mutex);
    return (SUCCESS);
}

int ft_fork_left(t_philosophe *philo)
{
    pthread_mutex_lock(philo->fork_left);
    if (check_is_dead(philo) == SUCCESS)
    {
        pthread_mutex_unlock(philo->fork_right);
        pthread_mutex_unlock(philo->fork_left);
        return (ERROR);
    }
    pthread_mutex_lock(&philo->arg->last_eat_mutex);
    printf(BLUE "%ld %d has taken a fork"RESET_COLOR"\n", get_time_diff(philo->last_eat),philo->id);
    pthread_mutex_unlock(&philo->arg->last_eat_mutex);
    return (SUCCESS);
}

void ft_is_eating(t_philosophe *philo)
{
    pthread_mutex_lock(&philo->arg->last_eat_mutex);
    printf(RED"\t\t%ld %d is eating"RESET_COLOR"\n", get_time_diff(philo->last_eat),philo->id);
    pthread_mutex_unlock(&philo->arg->last_eat_mutex);
    pthread_mutex_lock(&philo->arg->last_eat_mutex);
    philo->last_eat = get_time();
    pthread_mutex_unlock(&philo->arg->last_eat_mutex);
    ft_usleep(philo->arg->time_to_eat);
    pthread_mutex_unlock(philo->fork_right);
    pthread_mutex_unlock(philo->fork_left);
    ft_update_nb_eat(philo);
}

int ft_is_spleeping(t_philosophe *philo)
{
    if (check_is_dead(philo) == SUCCESS)
            return (ERROR);
    printf(MAGENTA"\t%ld %d is sleeping"RESET_COLOR"\n", get_time_diff(philo->last_eat),philo->id);
    ft_usleep(philo->arg->time_to_sleep);
    return (SUCCESS);
}
void ft_is_thinking(t_philosophe *philo)
{
    pthread_mutex_lock(&philo->arg->last_eat_mutex);
    printf(GREEN"\t\t\t%ld %d is thinking"RESET_COLOR"\n", get_time_diff(philo->last_eat),philo->id);
    pthread_mutex_unlock(&philo->arg->last_eat_mutex);
}
