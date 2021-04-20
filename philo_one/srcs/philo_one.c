/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:36:11 by ncolin            #+#    #+#             */
/*   Updated: 2021/04/20 15:01:04 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

void	*routine(void *ptr)
{
	t_philo	*philo;
	t_env	*env;
	env = get_env();
	philo = (t_philo *)ptr;
	while (!env->dinner_is_over)
	{
		if (env->number_of_meals && env->number_of_meals <= philo->meals_eaten)
			break ;
		philo_grab_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		write(1, "Test\n", 6);
	}
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

void check_philo_death(t_philo *philo)
{
	t_env *env;

	env = get_env();
	if (env->dinner_is_over)
		return ;
	if (get_microsec() - philo->last_meal >= env->time_to_die * 1000)
	{
		pthread_mutex_unlock(&env->mutex);
		philo_state(philo, "died\n");
		write(1, "died\n", 6);
		exit(0);
		env->dinner_is_over = 1;
		philo->alive = 0;
		pthread_mutex_lock(&env->mutex);
	}
}

void check_deaths(t_env *env)
{
	int i;

	while (env->number_of_philo_alive == env->number_of_philo && !env->dinner_is_over)
	{
		i = 0;
		while ( i < env->number_of_philo)
		{
			pthread_mutex_lock(&env->mutex);
			check_philo_death(&env->philos[i]);
			pthread_mutex_unlock(&env->mutex);
			i++;
		}
		ft_usleep(get_microsec(), 1000);
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
	check_deaths(env);
	end_dinner();
	free_all();
	return (0);
}
