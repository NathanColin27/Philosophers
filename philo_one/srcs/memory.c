/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 08:41:06 by nathan            #+#    #+#             */
/*   Updated: 2021/04/24 17:10:50 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** Adds the element new at the end of the list.
*/

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*ptr;

	if (!alst)
		return ;
	if (!*alst)
		*alst = new;
	else if (alst && *alst)
	{
		ptr = *alst;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

void	*append_ptr_list(void *ptr)
{
	t_list	*node;

	node = ft_lstnew(ptr);
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	ft_lstadd_back(&get_env()->ptrs_to_free, node);
	return (ptr);
}

void	*malloc_to_list(size_t elem_size, size_t elem_number)
{
	void	*ptr;

	ptr = malloc(elem_size * elem_number);
	if (!ptr)
		return (NULL);
	if (!append_ptr_list(ptr))
		return (NULL);
	return (ptr);
}

void	ft_free_list(void)
{
	t_env		*env;
	t_list		*tmp;

	env = get_env();
	tmp = env->ptrs_to_free;
	while (env->ptrs_to_free != NULL)
	{
		tmp = env->ptrs_to_free;
		env->ptrs_to_free = env->ptrs_to_free->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
}

// void	free_all(t_env	*env)
// {
// 	int	i;

// 	i = 0;
// 	(void)env;
// 	usleep(500000);
// 	// while (i < env->number_of_philo)
// 	// {
// 	// 	pthread_mutex_unlock(&env->forks[i].lock);
// 	// 	pthread_mutex_destroy(&env->forks[i].lock);
// 	// 	i++;
// 	// }
// 	ft_free_list();
// 	return ;
// }

int	error_exit(char *msg)
{
	printf("%s\n", msg);
	ft_free_list();
	return (1);
}
