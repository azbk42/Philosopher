#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* ************************************************************************** */
/*                                     DEFINE                                 */
/* ************************************************************************** */

# define ERROR_ARGS 1
# define ERROR_INIT_ARGS 2
# define ERROR_DATA 3
# define ERROR_PHILO 4
# define ERROR -1
# define SUCCESS 0

/* ************************************************************************** */
/*                                     COLOR                                  */
/* ************************************************************************** */

# define RESET_COLOR "\033[0m"

# define BLACK "\033[30m"   /* Black */
# define RED "\033[31m"     /* Red */
# define GREEN "\033[32m"   /* Green */
# define YELLOW "\033[33m"  /* Yellow */
# define BLUE "\033[34m"    /* Blue */
# define MAGENTA "\033[35m" /* Magenta */
# define CYAN "\033[36m"    /* Cyan */
# define WHITE "\033[37m"   /* White */

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
	bool					state_eat;
	bool					is_dead;
	pthread_mutex_t			state_eat_mutex;
	pthread_mutex_t			nb_eat_mutex;
	pthread_mutex_t			last_eat_mutex;
	pthread_mutex_t			is_dead_mutex;
};

struct						s_philosophe
{
	t_argument				*arg;
	int						id;
	pthread_mutex_t			*fork_right;
	pthread_mutex_t			*fork_left;
	int						fork_left_id;
	int						fork_right_id;
	int						nb_eat;
	unsigned long			last_eat;
};

struct						s_data
{
	t_argument				*arg;

	t_philosophe			*philosophe;
	pthread_t				check_die;
	pthread_t				check_eat;
	pthread_t				*thread;
	pthread_mutex_t			*forks;
};

/* ************************************************************************** */
/*                                   CHECK_STATE                              */
/* ************************************************************************** */

int							check_is_dead(t_philosophe *philo);
int							check_nb_eat(t_philosophe *philo);
void						ft_update_nb_eat(t_philosophe *philo);

/* ************************************************************************** */
/*                                  FILL_ARG                                  */
/* ************************************************************************** */

int							fill_arg(t_argument *arg, char **av);
void						fill_philo(t_data *data, int i);

/* ************************************************************************** */
/*                                  FREE_FUNCTION                             */
/* ************************************************************************** */

int							free_error_init(pthread_t *thread,
								pthread_mutex_t *forks, int i, t_data *data);
void						free_data(t_data *data);
void						free_mutex(t_data *data);

/* ************************************************************************** */
/*                                 INITIALISATION                             */
/* ************************************************************************** */

int							init_arg(t_argument *philo, char **av);
int							init_data(t_argument *philo, t_data *data);
int							init_philo(t_data *data);

/* ************************************************************************** */
/*                                     IS_DOING                               */
/* ************************************************************************** */

int							ft_fork_right(t_philosophe *philo);
int							ft_fork_left(t_philosophe *philo);
void						ft_is_eating(t_philosophe *philo);
int							ft_is_spleeping(t_philosophe *philo);
void						ft_is_thinking(t_philosophe *philo);

/* ************************************************************************** */
/*                                     MONITOR                                */
/* ************************************************************************** */

void						*monitor_die(void *arg);
void						monitor_nb_eat(t_data *data);

/* ************************************************************************** */
/*                                     ROUTINE                                */
/* ************************************************************************** */

void						*eat_routine(void *arg);

/* ************************************************************************** */
/*                                     TIME                                   */
/* ************************************************************************** */

unsigned long				get_time(void);
unsigned long				get_time_diff(unsigned long start);
int							ft_usleep(size_t milliseconds);

/* ************************************************************************** */
/*                                     UTILS                                  */
/* ************************************************************************** */

int							ft_isdigit(int c);
int							ft_atoi(char *str);
int							parsing_arg(char **av);

#endif