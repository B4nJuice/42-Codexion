/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:40:21 by lgirard           #+#    #+#             */
/*   Updated: 2026/06/02 12:30:45 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include <stdio.h>
#include <stdlib.h>

int	malloc_error(void *param)
{
	free(param);
	fprintf(stderr, "Malloc ERROR.\n");
	return (1);
}

int	thread_destroy(t_global *global, int fail)
{
	int	i;

	i = 0;
	while (i < fail)
	{
		pthread_join(global->coders[i].thread, NULL);
		pthread_mutex_destroy(&(global->coders[i].mutex));
		pthread_mutex_destroy(&(global->dongles[i].mutex));
		i++;
	}
	pthread_mutex_destroy(&(global->start_mutex));
	pthread_mutex_destroy(&(global->print_mutex));
	pthread_mutex_destroy(&(global->stop_mutex));
	pthread_cond_destroy(&global->cond);
	return (1);
}
