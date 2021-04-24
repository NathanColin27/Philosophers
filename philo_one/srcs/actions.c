/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:14:00 by ncolin            #+#    #+#             */
/*   Updated: 2021/04/24 17:31:02 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	philo_eat(t_philo *philo, t_env *env)
{
	philo_grab_fork(philo);
	philo->last_meal = get_microsec();
	philo_state(philo, env, EATING);
	ft_usleep(philo->last_meal + env->time_to_eat * 1000);
	philo->fork_left->last_philo = philo->id;
	philo->fork_right->last_philo = philo->id;
	pthread_mutex_unlock(&philo->fork_left->lock);
	pthread_mutex_unlock(&philo->fork_right->lock);
	philo->meals_eaten++;
	philo_state(philo, env, SLEEPING);
	ft_usleep(philo->last_meal + env->time_to_eat * 1000 + \
								env->time_to_sleep * 1000);
	philo_state(philo, env, THINKING);
}

void	output(int state)
{
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
}

void	philo_state(t_philo *philo, t_env *env, int state)
{
	long	i;
	int		j;

	j = 0;
	i = get_microsec();
	pthread_mutex_lock(&env->mutex);
	if (env->dinner_is_over)
	{
		pthread_mutex_unlock(&env->mutex);
		return ;
	}
	ft_putnbr_fd((i - env->dinner_start) / 1000, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo->id + 1, 1);
	output(state);
	if (state == DEATH)
	{	
		env->dinner_is_over = 1;
		while (j++ < env->number_of_philo)
			pthread_mutex_unlock(&env->forks[j].lock);
		pthread_mutex_unlock(&env->mutex);
		return ;
	}
	pthread_mutex_unlock(&env->mutex);
}

void 	philo_grab_fork(t_philo *philo)
{
	t_env	*env;

	env = get_env();
	pthread_mutex_lock(&philo->fork_left->lock);
	philo_state(philo, env, GRAB_FORK);
	pthread_mutex_lock(&philo->fork_right->lock);
	philo_state(philo, env, GRAB_FORK);
}
