/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:37:14 by ncolin            #+#    #+#             */
/*   Updated: 2021/04/25 13:30:28 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>

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
# define WRITE_SEM "write"
# define MEALS_SEM "meals"
# define FORK_SEM "fork"

struct	s_env;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				meals_eaten;
	struct s_env	*env;
	pthread_t		thread;
}				t_philo;

typedef struct s_env
{
	int				number_of_philo;
	int				number_of_philo_full;
	long			current_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	long			dinner_start;
	int				dinner_is_over;
	sem_t			*write_sem;
	sem_t			*forks_sem;
	sem_t			*meals_sem;
	t_philo			*philos;
	t_list			*ptrs_to_free;
}				t_env;

/*
**	input
*/

int				parse_input(int ac, char **av);

/*
**	memory
*/

void			*malloc_to_list(size_t elem_size, size_t elem_number);

void			*append_ptr_list(void *ptr);

void			ft_free_list(void);

/*
**	errors
*/

int				error_exit(char *msg);

/*
**	env
*/

t_env			*get_env(void);

void			init_env(t_env *env);

void			init_philo(t_env *env);

void			init_forks(t_env *env);

/*
**	utils
*/

int				ft_atoi(const char *str);

t_list			*ft_lstnew(void *content);

long			get_microsec(void);

int				ft_strlen(char const *str);

/*
** print
*/

void			ft_putnbr_fd(long n, int fd);

void			ft_putstr_fd(char *str, int fd);

/*
**	actions
*/

void			philo_sleep(t_philo *philo);

void			philo_eat(t_philo *philo, t_env *env);

void			philo_think(t_philo *philo);

void			philo_grab_fork(t_philo *philo);

void			philo_state(t_philo *philo, t_env *env, int state);

void			ft_usleep(long end);

#endif
