/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_running.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 12:18:59 by lgirard           #+#    #+#             */
/*   Updated: 2026/05/28 12:33:44 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	stop_running(t_global *global)
{
	pthread_mutex_lock(&global->stop_mutex);
	global->stop = 1;
	pthread_mutex_unlock(&global->stop_mutex);
}