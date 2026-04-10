/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:30:00 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/17 14:12:05 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "coder.h"
#include "dongle.h"
#include "utils.h"
#include "monitoring.h"

static void	stop_and_join(pthread_t *threads, int n, int *stop)
{
	int	i;

	*stop = 1;
	i = 0;
	while (i < n)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_params			*params;
	t_coder				*coders;
	t_dongle			*dongles;
	pthread_t			*threads;
	t_thread_args		*args;
	t_monitoring_args	*margs;
	int				stop;
	int				i;

	params = fill_params(av, ac);
	if (!params)
		return (1);
	coders = create_coders(params->dongle_number);
	dongles = create_dongles(params->dongle_number);
	if (!coders || !dongles)
		return (malloc_error((void *)coders,
		(void *)dongles, (void *)params, NULL));
	start_timestamp();
	threads = malloc(sizeof(pthread_t) * (params->dongle_number + 1));
	if (!threads)
		return (malloc_error((void *)coders,
		(void *)dongles, (void *)params, (void *)threads));
	i = 0;
	stop = 0;
	while (i < params->dongle_number)
	{
		args = malloc(sizeof(t_thread_args));
		if (!args)
		{
			stop_and_join(threads, i, &stop);
			destroy_dongles(dongles, params->dongle_number);
			free(coders);
			free(params);
			free(threads);
			return (1);
		}
		args->coder = &coders[i];
		args->dongles = dongles;
		args->params = *params;
		args->stop = &stop;
		if (pthread_create(&threads[i], NULL, coder_routine, args) != 0)
		{
			free(args);
			stop_and_join(threads, i, &stop);
			destroy_dongles(dongles, params->dongle_number);
			free(coders);
			free(params);
			free(threads);
			return (1);
		}
		i++;
	}
	margs = malloc(sizeof(t_monitoring_args));
	if (!margs)
	{
		stop_and_join(threads, i, &stop);
		destroy_dongles(dongles, params->dongle_number);
		free(coders);
		free(params);
		free(threads);
		return (1);
	}
	margs->coders = &coders;
	margs->params = *params;
	margs->stop = &stop;
	if (pthread_create(&threads[i], NULL, monitoring_routine, margs) != 0)
	{
		free(margs);
		stop_and_join(threads, i, &stop);
		destroy_dongles(dongles, params->dongle_number);
		free(coders);
		free(params);
		free(threads);
		return (1);
	}
	pthread_join(threads[i], NULL);
	i = 0;
	while (i < params->dongle_number)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	destroy_dongles(dongles, params->dongle_number);
	free(coders);
	free(params);
	free(threads);
	return (0);
}
