/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:14:00 by ncolin            #+#    #+#             */
/*   Updated: 2021/04/23 17:24:01 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void philo_eat(t_philo *philo, t_env *env)
{
	philo_grab_fork(philo);
	philo->last_meal = get_microsec();
	philo_state(philo, EATING);
	ft_usleep(philo->last_meal + env->time_to_eat * 1000);
	philo->fork_left->last_philo = philo->id;
	philo->fork_right->last_philo = philo->id;
	pthread_mutex_unlock(&philo->fork_left->lock);
	pthread_mutex_unlock(&philo->fork_right->lock);
	philo->meals_eaten++;
	philo_state(philo, SLEEPING);
	ft_usleep(philo->last_meal + env->time_to_eat * 1000 + env->time_to_sleep * 1000);
	philo_state(philo, THINKING);
}

void philo_state(t_philo *philo, int state)
{
	t_env	*env;
	int i;

	i = -1;
	env = get_env();
	if (env->dinner_is_over)
		return ;
	pthread_mutex_lock(&env->mutex);
	ft_putnbr_fd((get_microsec() - env->dinner_start)/1000, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo->id + 1, 1);
	if (state == GRAB_FORK)
		write(1, GRAB_FORK_MSG, GRAB_FORK_MSG_LEN);
	else if (state == EATING)
		write(1, EAT_MSG, EAT_MSG_LEN);
	else if (state == SLEEPING)
		write(1, SLEEP_MSG, SLEEP_MSG_LEN);
	else if (state == THINKING)
		write(1, THINK_MSG, THINK_MSG_LEN);
	else if (state == DEATH)
		write(1, DEATH_MSG, DEATH_MSG_LEN);
	if (state == DEATH)
	{
		env->dinner_is_over = 1;
		return ;
	}
	pthread_mutex_unlock(&env->mutex);
	
}

void 	philo_grab_fork(t_philo *philo)
{
		pthread_mutex_lock(&philo->fork_left->lock);
		philo_state(philo, GRAB_FORK);
		pthread_mutex_lock(&philo->fork_right->lock);
		philo_state(philo, GRAB_FORK);
}
