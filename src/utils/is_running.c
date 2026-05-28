/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_running.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 09:13:05 by lgirard           #+#    #+#             */
/*   Updated: 2026/05/28 10:30:30 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int is_running(t_global *global)
{
	int	status;

	pthread_mutex_lock(&global->stop_mutex);
	status = !(global->stop);
	pthread_mutex_unlock(&global->stop_mutex);
	return status;
}