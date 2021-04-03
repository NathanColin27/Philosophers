/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:42:46 by ncolin            #+#    #+#             */
/*   Updated: 2021/04/03 10:15:06 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#define MAXLONG 9223372036854775807

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
		else if (sign == 1)
			return ((int) MAXLONG);
		else
			return ((int)(-MAXLONG - 1));
	}
	total_int = total;
	return (total_int * sign);
}

/*
**	Allocates (with malloc(3)) and returns a new element. The variable content
**  is initialized with the value of the parameter content. The variable
**  next is initialized to NULL.
*/

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

