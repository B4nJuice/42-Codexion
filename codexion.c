/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:30:00 by lgirard           #+#    #+#             */
/*   Updated: 2026/05/21 09:10:48 by lgirard          ###   ########lyon.fr   */
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

int main(int ac, char **av)
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
	threads = malloc(sizeof(pthread_t) * (params->dongle_number + 1));
	if (!threads)
		return (malloc_error((void *)coders,
		(void *)dongles, (void *)params, (void *)threads));
	i = 0;
	stop = 0;
	start_timestamp();
	while (i < params->dongle_number)
	{
		args = malloc(sizeof(t_thread_args));
		args->coder = &coders[i];
		args->dongles = dongles;
		args->params = *params;
		args->stop = &stop;
		pthread_create(&threads[i], NULL, coder_routine, args);
		i++;
	}
	margs = malloc(sizeof(t_monitoring_args));
	margs->coders = &coders;
	margs->params = *params;
	margs->stop = &stop;
	pthread_create(&threads[i], NULL, monitoring_routine, margs);
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
