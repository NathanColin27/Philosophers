/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:36:11 by ncolin            #+#    #+#             */
/*   Updated: 2021/04/24 18:23:06 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*routine(void *ptr)
{
	t_philo	*philo;
	t_env	*env;

	env = get_env();
	philo = (t_philo *)ptr;
	while (!env->dinner_is_over)
	{
		philo_eat(philo, env);
		if (env->number_of_meals && env->number_of_meals == philo->meals_eaten)
			env->number_of_philo_full++;
		if (env->number_of_philo_full == env->number_of_philo)
		{
			env->dinner_is_over = 1;
			return (ptr);
		}
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
		i += 2;
		usleep(20);
	}
	i = 1;
	usleep(100);
	while (i < env->number_of_philo)
	{
		if (pthread_create(&env->philos[i].thread, NULL, \
			&routine, (void *)&env->philos[i]))
			error_exit("thread creation failed");
		i += 2;
		usleep(20);
	}
}

void	end_dinner(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->number_of_philo)
	{
		pthread_join(env->philos[i].thread, NULL);
		i++;
	}
}

void	check_deaths(t_env *env)
{
	int		i;
	long	time;

	while (!env->dinner_is_over)
	{
		i = 0;
		time = get_microsec();
		while (i < env->number_of_philo && !env->dinner_is_over)
		{
			if (time - env->philos[i].last_meal >= env->time_to_die * 1000)
			{
				philo_state(&env->philos[i], env, DEATH);
				return ;
			}
			i++;
		}
		usleep(500);
	}
}

int	main(int ac, char **av)
{
	t_env	*env;

	env = get_env();
	if (parse_input(ac, av))
		return (1);
	init_env(env);
	init_forks(env);
	init_philo();
	start_dinner();
	check_deaths(env);
	end_dinner(env);
	ft_free_list();
	return (0);
}
