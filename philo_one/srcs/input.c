/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 09:29:25 by nathan            #+#    #+#             */
/*   Updated: 2021/04/15 15:18:45 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	check_args(int argc, t_env *env)
{
	if (!env->number_of_philo || !env->time_to_die || !env->time_to_eat || \
		!env->time_to_sleep)
		error_exit("Args not correctly set");
	else if (argc == 6 && env->number_of_meals <= 0)
		error_exit("Args not correctly set");
	else if (env->number_of_philo * env->time_to_die * env->time_to_eat \
			* env->time_to_sleep < 0 )
		error_exit("Args can not be negatives");
}

void	parse_input(int ac, char **av)
{
	t_env	*env;

	env = get_env();
	if (ac < 5 || ac > 6)
		error_exit("Enter between 4 and 5 args");
	env->number_of_philo = ft_atoi(av[1]);
	env->time_to_die = ft_atoi(av[2]);
	env->time_to_eat = ft_atoi(av[3]);
	env->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		env->number_of_meals = ft_atoi(av[5]);
	check_args(ac, env);
}
