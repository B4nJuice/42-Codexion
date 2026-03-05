/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:08:20 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/04 12:26:54 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "dongle.h"

int	take_dongle(t_coder *coder, t_dongle *dongle_array, int dongle_number)
{
	t_dongle	*left_dongle;
	t_dongle	*right_dongle;

	left_dongle = get_dongle(coder->index, dongle_array, dongle_array);
	right_dongle = get_dongle(coder->index + 1, dongle_array, dongle_array);
	if (left_dongle->taken || right_dongle->taken)
		return 0;

	coder->left_hand = 1;
	coder->right_hand = 1;
	return 1;
}