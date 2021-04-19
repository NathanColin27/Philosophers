/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:04:29 by ncolin            #+#    #+#             */
/*   Updated: 2021/04/19 12:18:01 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	init_env(t_env *env)
{
	env->ptrs_to_free = NULL;
	env->philos = malloc_to_list(sizeof(t_philo), env->number_of_philo);
	if (!env->philos)
		error_exit("Philos's malloc failed");
	env->forks = malloc_to_list(sizeof(t_fork), env->number_of_philo);
	if (!env->forks)
		error_exit("Forks's malloc failed");
	pthread_mutex_init(&env->mutex, NULL);
	env->number_of_philo_alive = env->number_of_philo;
	env->number_of_philo_full = 0;
	env->dinner_is_over = 0;
}

void	init_forks(void)
{
	t_env	*env;
	int		i;

	env = get_env();
	i = 0;
	while (i < env->number_of_philo)
	{
		env->forks[i].id = i;
		if (pthread_mutex_init(&env->forks[i].lock, NULL))
			error_exit("mutex init failed");
		i++;
	}
}

void	init_philo(void)
{
	t_env	*env;
	int		i;

	env = get_env();
	i = 0;
	while (i < env->number_of_philo)
	{
		env->philos[i].alive = 1;
		env->philos[i].meals_eaten = 0;
		env->philos[i].last_meal = get_microsec();
		env->philos[i].id = i;
		env->philos[i].state = THINKING;
		env->philos[i].fork_left = &env->forks[i].lock;
		env->philos[i].fork_right = &env->forks[(i+1)%env->number_of_philo].lock;
		i++;
	}
}
