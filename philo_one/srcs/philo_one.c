/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:36:11 by ncolin            #+#    #+#             */
/*   Updated: 2021/04/15 15:25:17 by ncolin           ###   ########.fr       */
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
	int		start;

	start = get_microsec();
	env = get_env();
	philo = (t_philo *)ptr;
	pthread_mutex_lock(&env->mutex);
	printf("Here is philo number %d\n", philo->id);
	printf("%d microsec elapsed \n", get_microsec() - start);
	pthread_mutex_unlock(&env->mutex);
	return (ptr);
}

void	start_dinner(void)
{
	t_env	*env;
	int		i;

	env = get_env();
	i = 0;
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
