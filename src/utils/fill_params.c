/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 09:42:23 by lgirard           #+#    #+#             */
/*   Updated: 2026/06/01 12:51:24 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int		are_params_valid(t_params *params);
void	get_params(t_params *params, char **argv);

int	fill_params(char **argv, int argc, t_params *params)
{
	if (argc != 9)
	{
		fprintf(stderr, "Invalid arguments, try: ./codexion [number_of_coders]\
[time_to_burnout] [time_to_compile] [time_to_debug] [time_to_refactor]\
[number_of_compiles_required] [dongle_cooldown] [scheduler]\n");
		return (1);
	}
	get_params(params, argv);
	if (!are_params_valid(params))
		return (1);
	return (0);
}

void	get_params(t_params *params, char **argv)
{
	params->dongle_number = atoi(argv[1]);
	params->burnout_time = atoi(argv[2]);
	params->compiling_time = atoi(argv[3]);
	params->debugging_time = atoi(argv[4]);
	params->refactoring_time = atoi(argv[5]);
	params->required_compile = atoi(argv[6]);
	params->dongle_cooldown = atoi(argv[7]);
	if (!strcmp(argv[8], "fifo"))
		params->scheduler = FIFO;
	if (!strcmp(argv[8], "edf"))
		params->scheduler = EDF;
	params->scheduler_text = argv[8];
}

int	are_params_valid(t_params *params)
{
	if (params->burnout_time < 0 || params->compiling_time < 0 || \
params->debugging_time < 0 || params->refactoring_time < 0 || \
params->dongle_cooldown < 0)
	{
		fprintf(stderr, "All parameters have to be positive integers.\n");
		return (0);
	}
	if (strcmp(params->scheduler_text, "edf") && strcmp(params->scheduler_text, "fifo"))
	{
		fprintf(stderr, "Scheduler have to be either \"fifo\" or \"edf\"\n");
		return (0);
	}
	return (1);
}
