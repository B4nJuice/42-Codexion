/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:30:53 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/10 10:31:27 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

void	*coder_routine(void *arg)
{
	t_thread_args	*args;

	args = (t_thread_args *)arg;
	take_dongles(args->coder, args->dongles, args->dongle_number);
	codexion_log(*(args->coder), "is compiling");
	usleep(args->compiling_time*1000);
	release_dongles(args->coder, args->dongles, args->dongle_number);
	codexion_log(*(args->coder), "is debugging");
	usleep(args->debugging_time*1000);
	codexion_log(*(args->coder), "is refactoring");
	usleep(args->refactoring_time*1000);
	free(args);
	return (NULL);
}
