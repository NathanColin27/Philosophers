/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:12:51 by ncolin            #+#    #+#             */
/*   Updated: 2021/03/23 12:39:13 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *dice(void *arg)
{	

	int value = (rand() % 100) + 1;
	int index = *(int*)arg;
	int *res = malloc((sizeof(int)));
	*res = value;
	printf("in thread %d : res = %i \n", index,  value);
	return (void *) res;
}

int main(void)
{
	int *result;
	int i = 0;
	srand(time(NULL));
	pthread_t test[10];
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);
	while (i < 10)
	{
		if (pthread_create(&test[i], NULL, &dice, &i) != 0 )
			return (1);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (pthread_join(test[i],  (void **)&result) != 0)
			return (2);
		printf("thread %d ended: result %d\n", i, *result);
		free(result);
		i++;
	}
	
}