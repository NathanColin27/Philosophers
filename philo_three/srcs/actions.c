/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:14:00 by ncolin            #+#    #+#             */
/*   Updated: 2021/04/25 16:24:11 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	philo_eat(t_philo *philo, t_env *env)
{
	sem_wait(env->forks_sem);
	philo_state(philo, env, GRAB_FORK);
	sem_wait(env->forks_sem);
	philo_state(philo, env, GRAB_FORK);
	philo->last_meal = get_microsec();
	philo_state(philo, env, EATING);
	ft_usleep(philo->last_meal + env->time_to_eat * 1000);
	sem_post(env->forks_sem);
	sem_post(env->forks_sem);
	philo->meals_eaten++;
	philo_state(philo, env, SLEEPING);
	ft_usleep(philo->last_meal + env->time_to_eat * 1000 + \
								env->time_to_sleep * 1000);
	philo_state(philo, env, THINKING);
}

// void	output(int state)
// {
// 	if (state == GRAB_FORK)
// 		write(1, GRAB_FORK_MSG, GRAB_FORK_MSG_LEN);
// 	else if (state == EATING)
// 		write(1, EAT_MSG, EAT_MSG_LEN);
// 	else if (state == SLEEPING)
// 		write(1, SLEEP_MSG, SLEEP_MSG_LEN);
// 	else if (state == THINKING)
// 		write(1, THINK_MSG, THINK_MSG_LEN);
// 	else if (state == DEATH)
// 		write(1, DEATH_MSG, DEATH_MSG_LEN);
// }

void	philo_state(t_philo *philo, t_env *env, int state)
{
	long time;

	time = get_microsec();
	sem_wait(env->write_sem);
	if (env->dinner_is_over)
	{
		sem_post(env->write_sem);
		return ;
	}
	ft_putnbr_fd((time - env->dinner_start) / 1000, 1);
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
		env->dinner_is_over = 1;
	sem_post(env->write_sem);
}

// void 	philo_grab_fork(t_philo *philo)
// {
// 	t_env	*env;

// 	env = get_env();
// 	sem_wait(env->forks_sem);
// 	philo_state(philo, env, GRAB_FORK);
// 	sem_wait(env->forks_sem);
// 	philo_state(philo, env, GRAB_FORK);
// }
