/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:30:53 by lgirard           #+#    #+#             */
/*   Updated: 2026/05/28 15:20:00 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "core.h"
#include "utils.h"

static void	ft_wait(t_global *global, int time_to_wait)
{
	int start;

	start = get_timestamp();
	while (is_running(global) && get_timestamp() < start + time_to_wait)
	{
		usleep(100);
	}
}

void	wait_to_start(t_global *global)
{
	pthread_mutex_lock(&global->start_mutex);
	while (global->start_status == 0)
		pthread_cond_wait(&global->cond, &global->start_mutex);
	pthread_mutex_unlock(&global->start_mutex);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	wait_to_start(coder->global);
	if (coder->index % 2 == 1)
		usleep(1500);
	while (is_running(coder->global))
	{
		take_dongles(coder);
		coder->state = COMPILING;
		codexion_log(coder, "is compiling");
		pthread_mutex_lock(&(coder->mutex));
		coder->last_compilation = get_timestamp();
		pthread_mutex_unlock(&(coder->mutex));
		ft_wait(coder->global, coder->global->params.compiling_time);
		release_dongle(coder->first_dongle, 1);
		release_dongle(coder->second_dongle, 1);
		pthread_mutex_lock(&(coder->mutex));
		coder->compilation_number++;
		pthread_mutex_unlock(&(coder->mutex));
		if (coder->compilation_number >= coder->global->params.required_compile)
			break ;
		coder->state = DEBUGGING;
		codexion_log(coder, "is debugging");
		ft_wait(coder->global, coder->global->params.debugging_time);
		coder->state = REFACTORING;
		codexion_log(coder, "is refactoring");
		ft_wait(coder->global, coder->global->params.refactoring_time);
		coder->state = IDLE;
	}
	return (NULL);
}
