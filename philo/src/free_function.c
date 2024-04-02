/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emauduit <emauduit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:42:48 by emauduit          #+#    #+#             */
/*   Updated: 2024/04/02 17:59:47 by emauduit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int free_error_init(pthread_t *thread, pthread_mutex_t *forks, int i)
{
    
    if (i >= 0)
    {
        write(2, "Error: mutex init failed\n", 26);
    }
    else
    {
        write(2, "Error: malloc failed: data->forks\n", 22);
        free(thread);
    }
    while (i >= 0)
    {
        pthread_mutex_destroy(&forks[i]);
        i--;
    }
    if (forks)
        free(forks);
    return (ERROR);
}
void free_data(t_data *data)
{
    int i;
    
    i = 0;
    while (i < data->arg->nb_philo)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    free(data->forks);
    free(data->thread);
    free(data->philosophe);
}
