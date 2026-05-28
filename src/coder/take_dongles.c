/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:08:20 by lgirard           #+#    #+#             */
/*   Updated: 2026/05/28 12:46:27 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "core.h"
#include "utils.h"

int try_to_take(t_dongle *dongle, t_coder *coder)
{
	int	status;
	
	status = 0;
	pthread_mutex_lock(&dongle->mutex);
	if(!dongle->taken && dongle->last_time_taken + coder->global->params.dongle_cooldown <= get_timestamp())
	{
		dongle->taken = 1;
		status = 1;
	}
	pthread_mutex_unlock(&dongle->mutex);
	return status;
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
	}
	return (0);
	
}
