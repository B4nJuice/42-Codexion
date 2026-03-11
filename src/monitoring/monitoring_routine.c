/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 09:13:32 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/11 09:56:16 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "utils.h"
#include "monitoring.h"

void	*monitoring_routine(void *arg)
{
	t_monitoring_args	*args;
	t_params			params;
	t_coder				**coders;
	int					i;

	args = (t_monitoring_args *)arg;
	params = args->params;
	coders = args->coders;
	i = 0;
	while (i >= 0)
	{
		while (coders[i])
		{
			if (is_burned_out(coders[i], params.burnout_time) || \
is_compilation_satisfied(coders, params.required_compile))
			{
				i = -1;
				break ;
			}
			i++;
		}
	}
}

int	is_compilation_satisfied(t_coder **coders, int required_compile)
{
	int	i;

	i = 0;
	while (coders[i])
	{
		if (coders[i]->compilation_number < required_compile)
			return (0);
		i++;
	}
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
