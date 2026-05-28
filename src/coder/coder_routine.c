/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:30:53 by lgirard           #+#    #+#             */
/*   Updated: 2026/05/28 11:21:49 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "core.h"
#include "utils.h"

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	// while (!*(global->stop))
	// {
	// 	take_dongles(global->coder, global->dongles, global->params.dongle_number);
	// 	codexion_log(*(global->coder), "is compiling");
	// 	global->coder->state = COMPILING;
	// 	global->coder->last_compilation = get_timestamp();
	// 	usleep(global->params.compiling_time*1000);
	// 	release_dongles(global->coder, global->dongles, global->params.dongle_number);
	// 	global->coder->compilation_number++;
	// 	global->coder->state = DEBUGGING;
	// 	codexion_log(*(global->coder), "is debugging");
	// 	usleep(global->params.debugging_time*1000);
	// 	global->coder->state = REFACTORING;
	// 	codexion_log(*(global->coder), "is refactoring");
	// 	usleep(global->params.refactoring_time*1000);
	// 	global->coder->state = IDLE;
	// }
	// free(global);
	return (NULL);
}
