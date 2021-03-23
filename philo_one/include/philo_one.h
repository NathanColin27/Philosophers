/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:37:14 by ncolin            #+#    #+#             */
/*   Updated: 2021/03/23 15:45:02 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <stdlib.h>
#define ERR_ARGNUM 1

typedef struct	s_env
{
	int		number_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_each_philo_must_eat;
	t_philo	*philos;
	t_fork	*fork;
}				t_env;

typedef struct	s_philo
{
	int id;
	
	/* data */
}				t_philo;

typedef struct	s_fork
{
	/* data */
}				t_fork;

int				ft_atoi(const char *str);

#endif // !PHILO_ONE_H
