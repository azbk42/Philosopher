/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emauduit <emauduit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:06:00 by azbk              #+#    #+#             */
/*   Updated: 2024/04/09 16:38:03 by emauduit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"



void *eat_routine(void *arg)
{
    t_philosophe *philo;
    
    philo = (t_philosophe *)arg;
    if (philo->id % 2 == 0)
        ft_usleep(philo->arg->time_to_eat - 10);
    while (true)
    {
        if (check_nb_eat(philo) == SUCCESS)
            break;
        if (check_is_dead(philo) == SUCCESS)
            break;
        else
        {
            pthread_mutex_lock(philo->fork_right);
            printf(YELLOW "\t\t\ttime = %ld philo nb %d has taken a fork right (%d)"RESET_COLOR"\n", get_time_diff(philo->last_eat),philo->id, philo->fork_right_id);
            pthread_mutex_lock(philo->fork_left);
            printf(BLUE "time = %ld philo nb %d has taken a fork left (%d)"RESET_COLOR"\n", get_time_diff(philo->last_eat),philo->id, philo->fork_left_id);
            printf(RED"\t\t time = %ld philo nb %d is eating"RESET_COLOR"\n", get_time_diff(philo->last_eat),philo->id);
            philo->last_eat = get_time();
            ft_usleep(philo->arg->time_to_eat);
            philo->nb_eat++;
            pthread_mutex_unlock(philo->fork_right);
            pthread_mutex_unlock(philo->fork_left);
        }
        
        if (check_is_dead(philo) == SUCCESS)
            break;
        else
        {
            printf(MAGENTA"\ttime = %ld philo nb %d is sleeping"RESET_COLOR"\n", get_time_diff(philo->last_eat),philo->id);
            ft_usleep(philo->arg->time_to_sleep);
        }
        
        if (check_is_dead(philo) == SUCCESS)
            break;
        else
            printf(GREEN"\t\t\ttime = %ld philo nb %d is thinking"RESET_COLOR"\n", get_time_diff(philo->last_eat),philo->id);
    }
    return (NULL);
}

void *monitor_die_routine(void *arg)
{
    t_data *data;
    int i;
    unsigned long time;

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
            time = get_time_diff(data->philosophe[i].last_eat);
            if (time > (unsigned long)data->arg->time_to_die)
            {
                printf(BLACK"%lu philo nb %d is dead"RESET_COLOR"\n", time, i+1);
                pthread_mutex_lock(&data->arg->is_dead_mutex);
                data->arg->is_dead = true;
                pthread_mutex_unlock(&data->arg->is_dead_mutex);
                return (NULL);
            }
            i++;
        }
    }
    return (NULL);
}

void monitor_nb_eat(t_data *data)
{
    int i;
    
    while (true)
    {
        i = 0;
        while (i < data->arg->nb_philo)
        {
            if (data->philosophe[i].nb_eat < data->arg->nb_time_eat)
                break;
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
    pthread_create(&data->check_die, NULL, monitor_die_routine, data);
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
    free_data(data);
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
    return (0);
}
