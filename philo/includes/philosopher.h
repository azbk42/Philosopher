#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdbool.h>

# define ERROR_ARGS 1
# define ERROR_INIT_ARGS 2
# define ERROR_DATA 3
# define ERROR_PHILO 4
# define ERROR -1
# define SUCCESS 0

/* ************************************************************************** */
/*                                     STRUCT                                  */
/* ************************************************************************** */

typedef struct s_argument	t_argument;
typedef struct s_data		t_data;
typedef struct s_philosophe	t_philosophe;

struct						s_argument
{
	int						nb_philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						nb_time_eat;
};

struct						s_philosophe
{
	t_argument				*arg;
	int						id;
	pthread_mutex_t			*fork_right;
	pthread_mutex_t			*fork_left;
	int						nb_time_eat;
	int						fork_left_id;
	int						fork_right_id;
};

struct						s_data
{
	t_argument				*arg;

	t_philosophe			*philosophe;
	pthread_t				*thread;
	pthread_mutex_t			*forks;
};

/* ************************************************************************** */
/*                                     FREE_FUNCTION                                  */
/* ************************************************************************** */

int							free_error_init(pthread_t *thread,
								pthread_mutex_t *forks, int i);
void						free_data(t_data *data);

/* ************************************************************************** */
/*                                 INITIALISATION                             */
/* ************************************************************************** */
int							init_arg(t_argument *philo, char **av);
int							init_data(t_argument *philo, t_data *data);
int							init_philo(t_data *data);

/* ************************************************************************** */
/*                                     UTILS                                  */
/* ************************************************************************** */

int							ft_isdigit(int c);
int							ft_atoi(char *str);
int							parsing_arg(char **av);

#endif