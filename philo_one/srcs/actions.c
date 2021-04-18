/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:14:00 by ncolin            #+#    #+#             */
/*   Updated: 2021/04/18 16:55:24 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void philo_sleep(t_philo *philo)
{
	int start;	
	t_env	*env;

	env = get_env();
	start = get_microsec();
	philo_state(philo, "sleeping\n");
	usleep(get_env()->time_to_sleep * 1000);
}

void philo_think(t_philo *philo)
{
	philo_state(philo, "thinking\n");
}

void philo_eat(t_philo *philo)
{
	t_env	*env;

	env = get_env();
	philo->last_meal = get_microsec();
	philo_state(philo, "eating\n");
	usleep(env->time_to_eat * 1000);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	philo_state(philo, "released forks\n");

}

void philo_state(t_philo *philo, char* state)
{
	t_env	*env;
	int		time;

	env = get_env();
	// pthread_mutex_lock(&env->mutex);
	time =  get_microsec();
	printf("|%d ms| Philo Number %d %s", (time - env->dinner_start) / 1000, philo->id + 1, state);
	// pthread_mutex_unlock(&env->mutex);
}

void philo_grab_fork(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->fork_left);
		pthread_mutex_lock(philo->fork_right);
		philo_state(philo, "grabbed forks\n");
	}
	else
	{
		usleep(1000);
		pthread_mutex_lock(philo->fork_left);
		pthread_mutex_lock(philo->fork_right);
		philo_state(philo, "grabbed forks\n");

	}
}