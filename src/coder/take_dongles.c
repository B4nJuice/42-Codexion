/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:08:20 by lgirard           #+#    #+#             */
/*   Updated: 2026/06/02 12:22:38 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include "core.h"
#include "utils.h"

static int	get_last_compilation(t_coder *coder)
{
	int	last_compilation;

	pthread_mutex_lock(&(coder->mutex));
	last_compilation = coder->last_compilation;
	if (coder->compilation_number >= coder->global->params.required_compile)
		last_compilation = 2147483647;
	pthread_mutex_unlock(&(coder->mutex));
	return (last_compilation);
}

void	ft_swap_dongle(t_dongle *dongle, t_scheduler scheduler)
{
	t_coder	*coder_temp;

	pthread_mutex_lock(&dongle->mutex);
	if (scheduler == FIFO || get_last_compilation(dongle->coder1) > \
get_last_compilation(dongle->coder2))
	{
		coder_temp = dongle->coder1;
		dongle->coder1 = dongle->coder2;
		dongle->coder2 = coder_temp;
	}
	pthread_mutex_unlock(&dongle->mutex);
}

int	try_to_take(t_dongle *dongle, t_coder *coder)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&dongle->mutex);
	if (dongle->coder1 == coder && !dongle->taken && dongle->last_time_taken + \
coder->global->params.dongle_cooldown <= get_timestamp())
	{
		dongle->taken = 1;
		status = 1;
	}
	pthread_mutex_unlock(&dongle->mutex);
	return (status);
}

int	take_dongles(t_coder *coder)
{
	while (is_running(coder->global))
	{
		if (try_to_take(coder->first_dongle, coder))
		{
			if (try_to_take(coder->second_dongle, coder))
			{
				codexion_log(coder, "has taken a dongle");
				codexion_log(coder, "has taken a dongle");
				return (0);
			}
			else
				release_dongle(coder->first_dongle, 0);
		}
		usleep(100);
	}
	return (0);
}
