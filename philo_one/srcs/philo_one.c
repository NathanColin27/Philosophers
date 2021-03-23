/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:36:11 by ncolin            #+#    #+#             */
/*   Updated: 2021/03/23 16:10:21 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_env	*get_env(void)
{
	static t_env *env;

	return (env);
}

int		parse_input(int ac, char **av)
{
	t_env *env;
	
	env = get_env();
	if (ac < 5 || ac > 6)
		error_exit(ERR_ARGNUM);
	env->number_of_philo = ft_atoi(av[1]);
	env->time_to_die = ft_atoi(av[2]);
	env->time_to_eat = ft_atoi(av[3]);
	env->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		env->number_of_times_each_philo_must_eat = ft_atoi(av[5]);
	return (check_args(env));
}

void	init_env(int ac, t_env *env)
{
	env = (t_env *)malloc(sizeof(t_env));
	
}

int		main(int ac, char **av)
{
	t_env *env;
	
	env = get_env();
	parse_input(ac, av);
	init_philo();
}