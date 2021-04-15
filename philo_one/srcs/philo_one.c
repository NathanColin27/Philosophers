/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:36:11 by ncolin            #+#    #+#             */
/*   Updated: 2021/04/15 16:37:14 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>

void	error_exit(char *msg)
{
	printf("%s\n", msg);
	free_all();
	exit(0);
}

t_env	*get_env(void)
{
	static t_env	env;

	return (&env);
}

void philo_state(t_philo *philo, char* state)
{
	t_env	*env;
	int		time;

	env = get_env();
	time =  get_microsec();
	printf("|%d ms| Philo Number %d is %s", (time - env->dinner_start) / 1000, philo->id + 1, state);
}

void philo_sleep(t_philo *philo)
{
	int start;	
	t_env	*env;

	env = get_env();
	pthread_mutex_lock(&env->mutex);
	start = get_microsec();
	philo_state(philo, "sleeping\n");
	usleep(get_env()->time_to_sleep * 1000);
}

void think(void)
{
	return ;
}

void philo_eat(t_philo *philo)
{
	t_env	*env;

	env = get_env();
	philo_state(philo, "eating\n");
	usleep(env->time_to_eat * 1000);
	pthread_mutex_unlock(&env->mutex);
	
	return ;
}

void	*routine(void *ptr)
{
	t_philo	*philo;
	t_env	*env;
	int		start;

	start = get_microsec();
	env = get_env();
	philo = (t_philo *)ptr;
	philo_sleep(philo);
	philo_eat(philo);
	return (ptr);
}

void	start_dinner(void)
{
	t_env	*env;
	int		i;

	env = get_env();
	i = 0;
	env->dinner_start = get_microsec();
	while (i < env->number_of_philo)
	{
		if (pthread_create(&env->philos[i].thread, NULL, \
			&routine, (void *)&env->philos[i]))
			error_exit("thread creation failed");
		i++;
	}
}

void	end_dinner(void)
{
	t_env	*env;
	int		i;

	env = get_env();
	i = 0;
	while (i < env->number_of_philo)
	{
		pthread_join(env->philos[i].thread, NULL);
		i++;
	}
}


int	main(int ac, char **av)
{
	t_env	*env;

	env = get_env();
	parse_input(ac, av);
	init_env(env);
	init_forks();
	init_philo();
	start_dinner();
	end_dinner();
	free_all();
	return (0);
}
