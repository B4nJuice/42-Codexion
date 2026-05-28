/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_running.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 09:13:05 by lgirard           #+#    #+#             */
/*   Updated: 2026/05/28 09:19:15 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

int is_running(t_thread_args *args)
{
	int	status;

	pthread_mutex_lock(&args->stop_mutex);
	status = !(args->stop);
	pthread_mutex_unlock(&args->stop_mutex);
	return status;
}