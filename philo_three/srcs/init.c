/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:04:29 by ncolin            #+#    #+#             */
/*   Updated: 2021/04/25 16:24:19 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

t_env	*get_env(void)
{
	static t_env	env;

	return (&env);
}

sem_t	*init_sem(const char* name, int count)
{
	sem_unlink(name);
	return (sem_open(name,O_CREAT, 0660, count));
}

void	init_env(t_env *env)
{
	env->ptrs_to_free = NULL;
	env->philos = malloc_to_list(sizeof(t_philo), env->number_of_philo);
	if (!env->philos)
		error_exit("Philos's malloc failed");
	env->forks_sem = init_sem(FORK_SEM, env->number_of_philo);
	env->write_sem = init_sem(WRITE_SEM, 1);
	env->meals_sem = init_sem(MEALS_SEM, 1);
	if (env->forks_sem == SEM_FAILED || env->write_sem == SEM_FAILED || env->meals_sem == SEM_FAILED)
		error_exit("Semaphore initialisation failed");
	env->number_of_philo_full = 0;
	env->dinner_is_over = 0;
}

void	init_philo(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->number_of_philo)
	{
		env->philos[i].meals_eaten = 0;
		env->philos[i].last_meal = get_microsec();
		env->philos[i].id = i;
		env->philos[i].env = env;
		i++;
	}
}