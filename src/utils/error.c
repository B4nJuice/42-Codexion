/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:40:21 by lgirard           #+#    #+#             */
/*   Updated: 2026/05/28 11:10:57 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include <stdio.h>
#include <stdlib.h>

int	malloc_error(void *param1, void *param2, void *param3)
{
	free(param1);
	free(param2);
	free(param3);
	fprintf(stderr, "Malloc ERROR.\n");
	return (1);
}

int	thread_destroy(t_global *global, int fail)
{
	int	i = 0;

	while(i < fail)
	{
		pthread_join(global->coders[i].thread, NULL);
		pthread_mutex_destroy(&(global->coders[i].mutex));
		pthread_mutex_destroy(&(global->dongles[i].mutex));
		i++;
	}
	return (1);
}