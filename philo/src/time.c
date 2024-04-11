/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emauduit <emauduit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:54:20 by emauduit          #+#    #+#             */
/*   Updated: 2024/04/11 18:29:00 by emauduit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

unsigned long	get_time(void)
{
    struct timeval	time;
    unsigned long	time_in_mill;

    gettimeofday(&time, NULL);
    time_in_mill = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return (time_in_mill);
}

unsigned long	get_time_diff(unsigned long start)
{
    return (get_time() - start);
}
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
