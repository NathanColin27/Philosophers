/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:37:14 by ncolin            #+#    #+#             */
/*   Updated: 2021/04/03 10:52:03 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <stdio.h>
# include "pthread.h"

# define ERR_ARGNUM 1
# define ERR_ARGNOTSET 2
# define ERR_ALLOC 3

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_philo
{
	int	id;
	int state;
	int alive;
	pthread_t	thread;
}				t_philo;

typedef struct s_fork
{
	int	id;
}				t_fork;

typedef struct s_env
{
	int		number_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_each_philo_must_eat;
	t_philo	*philos;
	t_fork	*forks;
	t_list	*ptrs_to_free;
}				t_env;

/*
**	input
*/

void	parse_input(int ac, char **av);

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

/*
**	utils
*/

int				ft_atoi(const char *str);

t_list			*ft_lstnew(void *content);

#endif
