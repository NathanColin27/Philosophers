/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:36:11 by ncolin            #+#    #+#             */
/*   Updated: 2021/04/25 17:29:33 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*check_deaths(void *ptr)
{
	t_env	*env;
	t_philo	*philo;
	long	time;

	env = get_env();
	philo = ptr;
	
	while (!env->dinner_is_over)
	{
		time = get_microsec();
		if (time - philo->last_meal >= env->time_to_die * 1000)
		{	
			philo_state(philo, env, DEATH);
			return (void*)0;
		}
		usleep(1);
	}
	return (void*)0;
}


int		*routine(t_philo *philo)
{
	t_env	*env;

	env = get_env();
	if (pthread_create(&philo->thread, NULL, &check_deaths, (void *)philo))
			error_exit("thread creation failed");
	while (!env->dinner_is_over)
	{
		philo_eat(philo, env);
		if (env->number_of_meals && env->number_of_meals == philo->meals_eaten)
		{
			sem_wait(env->meals_sem);
			env->number_of_philo_full++;
			sem_post(env->meals_sem);
		}
		if (env->number_of_philo_full >= env->number_of_philo)
		{
			env->dinner_is_over = 1;
			pthread_join(philo->thread, NULL);
			exit (0);
		}
	}
	pthread_join(philo->thread, NULL);
	exit (0);
}

void	start_dinner(t_env *env)
{
	int	i;
		i = 0;
	env->dinner_start = get_microsec();
	while (i < env->number_of_philo)
	{
		env->philos[i].pid = fork();
		if (env->philos[i].pid < 0)
			error_exit("process_creation failed");
		if (env->philos[i].pid == 0)
		{
			printf("process number %d created\n", i);
			routine(&env->philos[i]);
		}
		i++;
	}
	// while (i < env->number_of_philo)
	// {
	// 	if (pthread_create(&env->philos[i].thread, NULL, \
	// 		&routine, (void *)&env->philos[i]))
	// 		error_exit("thread creation failed");
	// 	i += 2;
	// 	usleep(20);
	// }
	// i = 1;
	// usleep(100);
	// while (i < env->number_of_philo)
	// {
	// 	if (pthread_create(&env->philos[i].thread, NULL, \
	// 		&routine, (void *)&env->philos[i]))
	// 		error_exit("thread creation failed");
	// 	i += 2;
	// 	usleep(20);
	// }
}

// void	end_dinner(t_env *env)
// {
// 	int		i;

// 	i = 0;
// 	while (i < env->number_of_philo)
// 	{
// 		pthread_join(env->philos[i].thread, NULL);
// 		i++;
// 	}
// }


int	main(int ac, char **av)
{
	t_env	*env;

	env = get_env();
	if (parse_input(ac, av))
		return (1);
	init_env(env);
	init_philo(env);
	start_dinner(env);
	// check_deaths(env);
	// end_dinner(env);
	ft_free_list();
	sem_unlink(WRITE_SEM);
	sem_unlink(FORK_SEM);
	return (0);
}
