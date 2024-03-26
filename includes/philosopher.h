#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#define ERROR_ARGS 1
#define ERROR -1
#define SUCCESS 0

typedef struct s_philo		t_philo;

struct s_philo
{
    int     nb_philo;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     nb_time_eat;
};

/* ************************************************************************** */
/*                                     UTILS                                  */
/* ************************************************************************** */

int	ft_isdigit(int c);
int ft_atoi(char *str);
int parsing_arg(char **av);

/* ************************************************************************** */
/*                                 INITIALISATION                             */
/* ************************************************************************** */
int init_philo(t_philo *philo, char **av);

#endif