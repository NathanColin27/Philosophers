/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:36:11 by ncolin            #+#    #+#             */
/*   Updated: 2021/04/03 10:36:06 by nathan           ###   ########.fr       */
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

void	init_env(t_env *env)
{
	env->ptrs_to_free = NULL;

	env->philos = malloc_to_list(sizeof(t_philo), env->number_of_philo);
	if (!env->philos)
		error_exit("Philos's malloc failed");
}

int	main(int ac, char **av)
{
	t_env	*env;

	env = get_env();
	parse_input(ac, av);
	init_env(env);
	// init_philo();
	
}

// create a function malloc_list;
// implement a list containing all allocated pointers
