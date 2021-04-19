/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:14:00 by ncolin            #+#    #+#             */
/*   Updated: 2021/04/19 17:29:07 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void philo_sleep(t_philo *philo)
{
	t_env	*env;

	env = get_env();
	if (!env->dinner_is_over)
	{
		philo_state(philo, "is sleeping\n");
		ft_usleep(get_microsec(), env->time_to_sleep * 1000);
	}
}

void philo_think(t_philo *philo)
{
	t_env *env;

	env = get_env();
	if (philo->alive && !env->dinner_is_over)
	{
		philo_state(philo, "is thinking\n");
	}
}

void philo_eat(t_philo *philo)
{
	t_env	*env;

	env = get_env();
	if (!env->dinner_is_over)
	{	
		philo_state(philo, "is eating\n");
		philo->last_meal = get_microsec();
		ft_usleep(philo->last_meal ,env->time_to_eat * 1000);
	}
	if (env->number_of_meals > 0)
	{
		philo->meals_eaten++;
		if (philo->meals_eaten == env->number_of_meals)
			env->number_of_philo_full++;
		if (env->number_of_philo_full == env->number_of_philo)
			env->dinner_is_over++;
	}
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void philo_state(t_philo *philo, char* state)
{
	t_env	*env;
	(void)state;
	env = get_env();
	if(!philo->alive || env->dinner_is_over)
		return ;
	pthread_mutex_lock(&env->mutex);
	// printf("[%d]	%d %s", (get_microsec() - env->dinner_start) / 1000, philo->id + 1, state);
	// write(1, state, 30);
	pthread_mutex_unlock(&env->mutex);
}

void philo_grab_fork(t_philo *philo)
{
	t_env *env;

	env = get_env();
	if (!env->dinner_is_over && philo->alive)
	{	
		if (philo->id % 2)
		{
			pthread_mutex_lock(philo->fork_left);
			philo_state(philo, "has taken a fork\n");
			pthread_mutex_lock(philo->fork_right);
			philo_state(philo, "has taken a fork\n");
		}
		else
		{
			ft_usleep(get_microsec(), 100);
			pthread_mutex_lock(philo->fork_left);
			philo_state(philo, "has taken a fork\n");
			pthread_mutex_lock(philo->fork_right);
			philo_state(philo, "has taken a fork\n");
		}
	}
}