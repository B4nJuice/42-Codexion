/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 09:13:32 by lgirard           #+#    #+#             */
/*   Updated: 2026/05/28 15:55:35 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "utils.h"
#include "monitoring.h"
#include <unistd.h>

int	check_coders(t_global *global);

static void	start(t_global *global)
{
	start_timestamp();
	pthread_mutex_lock(&global->start_mutex);
	global->start_status = 1;
	pthread_cond_broadcast(&(global->cond));
	pthread_mtex_unlock(&global->start_mutex);
}

void	start_monitor(t_global *global)
{
	start(global);
	while (is_running(global))
	{
		if (check_coders(global))
		{
			stop_running(global);	
			return ;
		}
		usleep(500);
	}
}

int	check_coders(t_global *global)
{
	int i;
	int status;
	
	i = 0;
	status = 1;
	while (i < global->params.dongle_number)
	{
		pthread_mutex_lock(&(global->coders[i].mutex));
		if (global->coders[i].compilation_number < global->params.required_compile)
			status = 0;
		if (global->coders[i].last_compilation + global->params.burnout_time <= get_timestamp())
		{
			codexion_log(&(global->coders[i]), "has burned out");
			pthread_mutex_unlock(&(global->coders[i].mutex));
			return (1);
		}
		pthread_mutex_unlock(&(global->coders[i].mutex));
		i++;
	}
	return (status);
}
