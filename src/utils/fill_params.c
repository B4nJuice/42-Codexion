/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 09:42:23 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/12 09:58:55 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "stdlib.h"

int	are_params_valid(t_params *params);

t_params	*fill_params(char **argv)
{
	t_params	*params;

	params = malloc(sizeof(t_params));
	if (!params)
		return (NULL);
	params->dongle_number = atoi(argv[0]);
	params->burnout_time = atoi(argv[1]);
	params->compiling_time = atoi(argv[2]);
	params->debugging_time = atoi(argv[3]);
	params->refactoring_time = atoi(argv[4]);
	params->required_compile = atoi(argv[5]);
	params->dongle_cooldown = atoi(argv[6]);
	params->scheduler = argv[7];
	if (!are_params_valid(params))
		return (NULL);
	return (params);
}

int	are_params_valid(t_params *params)
{
	if (params->dongle_number < 2)
		return (0);
	if (params->burnout_time < 0 || params->compiling_time < 0 || \
params->debugging_time < 0 || params->refactoring_time < 0 || \
params->dongle_cooldown < 0)
		return (0);
	if (strcmp(params->scheduler, "edf") && strcmp(params->scheduler, "fifo"))
		return (0);
	return (1);
}
