/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:30:53 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/11 09:43:42 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "utils.h"

void	*coder_routine(void *arg)
{
	t_thread_args	*args;

	args = (t_thread_args *)arg;
	take_dongles(args->coder, args->dongles, args->params.dongle_number);
	codexion_log(*(args->coder), "is compiling");
	args->coder->state = COMPILING;
	args->coder->last_compilation = get_timestamp();
	usleep(args->params.compiling_time*1000);
	release_dongles(args->coder, args->dongles, args->params.dongle_number);
	args->coder->compilation_number++;
	args->coder->state = DEBUGGING;
	codexion_log(*(args->coder), "is debugging");
	usleep(args->params.debugging_time*1000);
	args->coder->state = REFACTORING;
	codexion_log(*(args->coder), "is refactoring");
	usleep(args->params.refactoring_time*1000);
	args->coder->state = IDLE;
	free(args);
	return (NULL);
}
