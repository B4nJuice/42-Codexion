/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:08:20 by lgirard           #+#    #+#             */
/*   Updated: 2026/05/28 09:12:40 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "coder.h"
#include "dongle.h"
#include "utils.h"

int try_to_take(t_dongle *dongle, t_coder *coder)
{
	int	status;
	
	status = 0;
	pthread_mutex_lock(&dongle->mutex);
	if(!dongle->taken && dongle->last_time_taken + coder->params.dongle_cooldown <= get_timestamp())
	{
		dongle->taken = 1;
		status = 1;
	}
	pthread_mutex_unlock(&dongle->mutex);
	return status;
}


int	take_dongles(t_coder *coder, t_dongle *dongle_array, int dongle_number)
{
	t_dongle	*left_dongle;
	t_dongle	*right_dongle;
	
	left_dongle = get_dongle(coder->index, dongle_array, dongle_number);
	right_dongle = get_dongle(coder->index + 1, dongle_array, dongle_number);

	while ()
	{
		if (coder->first_check == LEFT)
		{
			if (try_to_take(left_dongle, coder))
			{
				if (try_to_take(right_dongle, coder))
					{
						codexion_log(*coder, "has taken a dongle");
						codexion_log(*coder, "has taken a dongle");
						coder->left_hand = 1;
						coder->right_hand = 1;
						return (0);
					}
				else
					left_dongle->taken = 0;
			}
			else
				left_dongle->taken = 0;
		}
	}
	
}
