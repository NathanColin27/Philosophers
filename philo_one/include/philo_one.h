/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:37:14 by ncolin            #+#    #+#             */
/*   Updated: 2021/04/23 15:06:54 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <stdio.h>
# include "pthread.h"
#include <unistd.h>

# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEATH 4
# define GRAB_FORK 5
# define EAT_MSG " is eating\n"
# define SLEEP_MSG " is sleeping\n"
# define THINK_MSG " is thinking\n"
# define DEATH_MSG " died\n"
# define GRAB_FORK_MSG " has taken a fork\n"
# define EAT_MSG_LEN 12
# define SLEEP_MSG_LEN 14 
# define THINK_MSG_LEN 14
# define DEATH_MSG_LEN 7
# define GRAB_FORK_MSG_LEN 19

struct s_env;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_fork
{
	int				last_philo;
	pthread_mutex_t	lock;
}				t_fork;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				state;
	int				alive;
	int				meals_eaten;
	struct s_env 	*env;
	pthread_t		thread;
	t_fork			*fork_left;
	t_fork			*fork_right;
}				t_philo;


typedef struct s_env
{
	int				number_of_philo;
	int				number_of_philo_alive;
	int				number_of_philo_full;
	long			current_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	long			dinner_start;
	int				dinner_is_over;
	pthread_mutex_t	mutex;
	t_philo			*philos;
	t_fork			*forks;
	t_list			*ptrs_to_free;
}				t_env;

/*
**	input
*/

void			parse_input(int ac, char **av);

/*
**	memory
*/

void			*malloc_to_list(size_t elem_size, size_t elem_number);
void			*append_ptr_list(void *ptr);
void			free_all(t_env	*env);

/*
**	errors
*/

void			error_exit(char *msg);

/*
**	env
*/

t_env			*get_env(void);

void			init_env(t_env *env);

void			init_philo(void);

void			init_forks(t_env *env);

/*
**	utils
*/

int				ft_atoi(const char *str);

t_list			*ft_lstnew(void *content);

long			get_microsec(void);

void			print_env(void);

void			ft_putstr_fd(char *str, int fd);

void			ft_putnbr_fd(long n, int fd);

int	ft_strlen(char const *str);

/*
**	actions
*/

void			philo_sleep(t_philo *philo);

void			philo_eat(t_philo *philo, t_env *env);

void			philo_think(t_philo *philo);

void			philo_grab_fork(t_philo *philo);

void			philo_state(t_philo *philo, int state);

void 			ft_usleep(long end);

#endif
