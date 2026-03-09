/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_dongle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:08:20 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/09 13:42:20 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "coder.h"
#include "dongle.h"

int	take_dongles(t_coder *coder, t_dongle *dongle_array, int dongle_number)
{
	t_dongle	*left_dongle;
	t_dongle	*right_dongle;

	left_dongle = get_dongle(coder->index, dongle_array, dongle_array);
	right_dongle = get_dongle(coder->index + 1, dongle_array, dongle_array);
	if (coder->first_check == LEFT)
	{
		pthread_mutex_lock(&left_dongle->mutex);
		pthread_mutex_lock(&right_dongle->mutex);
	}
	else
	{
		pthread_mutex_lock(&right_dongle->mutex);
		pthread_mutex_lock(&left_dongle->mutex);
	}
	left_dongle->taken = 1;
	right_dongle->taken = 1;
	coder->left_hand = 1;
	coder->right_hand = 1;
	return (0);
}
