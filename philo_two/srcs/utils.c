/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:42:46 by ncolin            #+#    #+#             */
/*   Updated: 2021/04/24 18:23:17 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <sys/time.h>

static int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || \
		c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	total;
	int		total_int;

	sign = 1;
	total = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (total <= total * 10 + (*str - '0'))
		{
			total = total * 10 + (*str - '0');
			str++;
		}
	}
	total_int = total;
	return (total_int * sign);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = (t_list *)malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}

void	ft_usleep(long end_time)
{
	usleep((end_time - get_microsec()) * 0.99);
	while (get_microsec() <= end_time)
	{	
		usleep(200);
	}
}

long	get_microsec(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}
