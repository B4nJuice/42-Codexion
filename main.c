/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:30:00 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/10 10:14:55 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "coder.h"
#include "dongle.h"
#include "utils.h"

typedef struct s_thread_args
{
	t_coder		*coder;
	t_dongle	*dongles;
	int			dongle_number;
}	t_thread_args;

void	*coder_routine(void *arg)
{
	t_thread_args	*args;

	args = (t_thread_args *)arg;
	take_dongles(args->coder, args->dongles, args->dongle_number);
	free(args);
	return (NULL);
}

int	main(void)
{
	int				num_coders;
	int				num_dongles;
	int				i;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_t		*threads;
	t_thread_args	*args;

	num_coders = 5;
	num_dongles = 5;

	printf("=== Codexion Test ===\n");
	printf("Creating %d coders and %d dongles...\n", num_coders, num_dongles);

	start_timestamp();

	coders = create_coders(num_coders);
	if (!coders)
	{
		printf("Error: Failed to create coders\n");
		return (1);
	}

	dongles = create_dongles(num_dongles);
	if (!dongles)
	{
		printf("Error: Failed to create dongles\n");
		free(coders);
		return (1);
	}

	threads = malloc(sizeof(pthread_t) * num_coders);
	if (!threads)
	{
		printf("Error: Failed to allocate threads\n");
		free(coders);
		destroy_dongles(dongles, num_dongles);
		return (1);
	}

	printf("Coders and dongles created successfully!\n");

	printf("Starting %d coder threads...\n", num_coders);
	i = 0;
	while (i < num_coders)
	{
		args = malloc(sizeof(t_thread_args));
		if (!args)
		{
			printf("Error: Failed to allocate thread args\n");
			free(threads);
			free(coders);
			destroy_dongles(dongles, num_dongles);
			return (1);
		}
		args->coder = &coders[i];
		args->dongles = dongles;
		args->dongle_number = num_dongles;
		pthread_create(&threads[i], NULL, coder_routine, args);
		i++;
	}

	printf("Waiting for threads to complete...\n");
	i = 0;
	while (i < num_coders)
	{
		pthread_join(threads[i], NULL);
		i++;
	}

	printf("Destroying dongles...\n");
	destroy_dongles(dongles, num_dongles);

	printf("Freeing resources...\n");
	free(coders);
	free(threads);

	printf("=== Test Complete ===\n");
	return (0);
}
