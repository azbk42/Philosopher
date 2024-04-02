/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emauduit <emauduit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:20:33 by azbk              #+#    #+#             */
/*   Updated: 2024/03/30 14:38:51 by emauduit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return (SUCCESS);
    return (ERROR);
}

int ft_atoi(char *str)
{
    int i;
    long res;

    i = 0;
    res = 0;
    while (str[i])
    {
        res = res * 10 + str[i] - '0';
        if (res > 2147483647)
            return (ERROR);
        i++;
    }   
    return (res);
}

int parsing_arg(char **av)
{
    size_t i;
    size_t j;
    
    i = 1;
    while (av[i])
    {   
        j = 0;
        while (av[i][j])
        {
            if (ft_isdigit(av[i][j]) == ERROR)
                return (ERROR);
            j++;
        }
        i++;
    }
    return (SUCCESS);
}
