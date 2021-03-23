/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:42:46 by ncolin            #+#    #+#             */
/*   Updated: 2021/03/23 15:42:50 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAXLONG 9223372036854775807

static int		ft_isspace(int c)
{
	return (c == '\t' || c == '\n' ||
		c == '\v' || c == '\f' || c == '\r' || c == ' ' ? 1 : 0);
}

int				ft_atoi(const char *str)
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
		sign = (*str == '-') ? -1 : 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (total <= total * 10 + (*str - '0'))
		{
			total = total * 10 + (*str - '0');
			str++;
		}
		else
			return (sign == 1 ? (int)MAXLONG : (int)-MAXLONG - 1);
	}
	total_int = total;
	return (total_int * sign);
}
