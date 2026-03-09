/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_dongles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:35:00 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/09 18:12:22 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "coder.h"
#include "dongle.h"

void	release_dongles(t_coder *coder, t_dongle *dongle_array,
	int dongle_number)
{
	t_dongle	*left_dongle;
	t_dongle	*right_dongle;

	left_dongle = get_dongle(coder->index, dongle_array, dongle_number);
	right_dongle = get_dongle(coder->index + 1, dongle_array, dongle_number);
	left_dongle->taken = 0;
	right_dongle->taken = 0;
	coder->left_hand = 0;
	coder->right_hand = 0;
	pthread_mutex_unlock(&left_dongle->mutex);
	pthread_mutex_unlock(&right_dongle->mutex);
}
