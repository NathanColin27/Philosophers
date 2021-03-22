/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:36:11 by ncolin            #+#    #+#             */
/*   Updated: 2021/03/22 15:02:40 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	parse_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		error_exit(ERR_ARGNUM);
}

int		main(int argc, char **argv)
{
	parse_input(argc, argv);
	init_game();
	init_philo();
	
}