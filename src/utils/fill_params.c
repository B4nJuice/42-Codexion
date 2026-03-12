/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 09:42:23 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/12 10:18:53 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int	are_params_valid(t_params *params);

t_params	*fill_params(char **av)
{
	t_params	*params;

	params = malloc(sizeof(t_params));
	if (!params)
	{
		fprintf(stderr, "Malloc ERROR.\n");
		return (NULL);
	}
	params->dongle_number = atoi(av[1]);
	params->burnout_time = atoi(av[2]);
	params->compiling_time = atoi(av[3]);
	params->debugging_time = atoi(av[4]);
	params->refactoring_time = atoi(av[5]);
	params->required_compile = atoi(av[6]);
	params->dongle_cooldown = atoi(av[7]);
	params->scheduler = av[8];
	if (!are_params_valid(params))
	{
		return (NULL);
		free(params);
	}
	return (params);
}

int	are_params_valid(t_params *params)
{
	if (params->dongle_number < 2)
	{
		fprintf(stderr, "numbers_of_coders have to be greater than one.\n");
		return (0);
	}
	if (params->burnout_time < 0 || params->compiling_time < 0 || \
params->debugging_time < 0 || params->refactoring_time < 0 || \
params->dongle_cooldown < 0)
	{
		fprintf(stderr, "All parameters have to be positive integers.\n");
		return (0);
	}
	if (strcmp(params->scheduler, "edf") && strcmp(params->scheduler, "fifo"))
	{
		fprintf(stderr, "Scheduler have to be either \"fifo\" or \"edf\"\n");
		return (0);
	}
	return (1);
}
