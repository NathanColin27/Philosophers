/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:37:14 by ncolin            #+#    #+#             */
/*   Updated: 2021/04/19 12:27:43 by ncolin           ###   ########.fr       */
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
# define DEAD 4

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_philo
{
	int				id;
	int				last_meal;
	int				state;
	int				alive;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t *fork_left;
	pthread_mutex_t *fork_right;
}				t_philo;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	lock;
}				t_fork;

typedef struct s_env
{
	int				number_of_philo;
	int				number_of_philo_alive;
	int				number_of_philo_full;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				dinner_start;
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
void			free_all(void);

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

void			init_forks(void);

/*
**	utils
*/

int				ft_atoi(const char *str);

t_list			*ft_lstnew(void *content);

int				get_microsec(void);

void			print_env(void);

/*
**	actions
*/

void			philo_sleep(t_philo *philo);

void			philo_eat(t_philo *philo);

void			philo_think(t_philo *philo);

void			philo_grab_fork(t_philo *philo);

void			philo_state(t_philo *philo, char* state);

void 			ft_usleep(int starting_time, int microsec);

#endif
