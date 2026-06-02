/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_dongle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:35:00 by lgirard           #+#    #+#             */
/*   Updated: 2026/05/28 12:46:09 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "core.h"
#include "utils.h"

void	release_dongle(t_dongle *dongle, int mode)
{
	pthread_mutex_lock(&dongle->mutex);
	if (mode)
		dongle->last_time_taken = get_timestamp();
	dongle->taken = 0;
	pthread_mutex_unlock(&dongle->mutex);
}