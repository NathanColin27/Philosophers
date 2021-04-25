/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:56:11 by ncolin            #+#    #+#             */
/*   Updated: 2021/04/25 16:24:40 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <sys/time.h>
#include <string.h>

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
}

void	reverse(char x[19], long begin, long end)
{
	char	c;

	if (begin >= end)
		return ;
	c = *(x + begin);
	*(x + begin) = *(x + end);
	*(x + end) = c;
	reverse(x, ++begin, --end);
}

void	ft_putnbr_fd(long n, int fd)
{
	char	str[19];
	int		length;

	if (n == 0)
		str[0] = '0';
	length = 0;
	while (n != 0)
	{
		str[length++] = '0' + (n % 10);
		n = (n / 10);
	}
	if (length > 0)
		length--;
	if (length)
		reverse(str, 0, length);
	write(fd, str, length + 1);
}
