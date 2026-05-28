/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_dongles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:21:55 by lgirard           #+#    #+#             */
/*   Updated: 2026/05/28 11:09:37 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "core.h"
#include "utils.h"
#include <pthread.h>

static void	fill_dongle(t_dongle *dongle)
{
	dongle->taken = 0;
	dongle->last_time_taken = 0;
}

int	create_dongles(t_global *global)
{
	int			i;

	global->dongles = malloc(global->params.dongle_number * sizeof(t_dongle));
	if (!global->dongles)
		return (malloc_error((void *)global->dongles,\
			(void *)global->coders, NULL));
	i = 0;
	while (i < global->params.dongle_number)
	{
		fill_dongle(&(global->dongles[i]));
		i++;
	}
	return (0);
}
