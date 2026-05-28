/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 09:13:32 by lgirard           #+#    #+#             */
/*   Updated: 2026/05/28 10:30:30 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "utils.h"
#include "monitoring.h"

int	is_burned_out(t_coder *coder, int burnout_time);
int	is_compilation_satisfied(t_coder *coder, int required_compile);

void	*monitoring_routine(void *arg)
{
	t_monitoring_global	*global;
	t_params			params;
	t_coder				**coders;
	int					i;

	global = (t_monitoring_global *)arg;
	params = global->params;
	coders = global->coders;
	while (1)
	{
		while (!*(global->stop))
		{
			i = 0;
			while (i < params.dongle_number)
			{
				if (is_burned_out(coders[i], params.burnout_time) || \
	is_compilation_satisfied(coders[i], params.required_compile))
				{
					*(global->stop) = 1;
					break ;
				}
				i++;
			}
		}
		return (NULL);
	}
}

#include <stdio.h>

int	is_compilation_satisfied(t_coder *coder, int required_compile)
{
	fprintf(stderr, "%i\n", coder->compilation_number);
	if (coder->compilation_number < required_compile)
		return (0);
	return (1);
}

int	is_burned_out(t_coder *coder, int burnout_time)
{
	int	actual_time;

	actual_time = get_timestamp();
	if (actual_time - coder->last_compilation > burnout_time && \
coder->state != COMPILING)
	{
		coder->state = BURNED_OUT;
		codexion_log(*coder, "burned out");
		return (1);
	}
	return (0);
}
