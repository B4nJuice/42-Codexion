/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_coders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:12:22 by lgirard           #+#    #+#             */
/*   Updated: 2026/05/28 12:48:32 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "stdio.h"
#include "core.h"
#include "utils.h"


void	fill_coder(t_coder *coder, int index, t_global *global)
{
	coder->index = index;
	coder->state = IDLE;
	coder->last_compilation = 0;
	coder->global = global;
}

int	create_coders(t_global *global)
{
	int					i;

	global->coders = malloc(global->params.dongle_number * sizeof(t_coder));
	if (!(global->coders))
		return (malloc_error((void *)global->coders, NULL, NULL));
	i = 0;
	while (i < global->params.dongle_number)
	{
		if (i == global->params.dongle_number - 1)
		{
			global->coders[i].first_dongle = get_dongle(i + 1, global->dongles, global->params.dongle_number);
			global->coders[i].second_dongle = get_dongle(i, global->dongles, global->params.dongle_number);
		}
		else
		{
			global->coders[i].first_dongle = get_dongle(i, global->dongles, global->params.dongle_number);
			global->coders[i].second_dongle = get_dongle(i + 1, global->dongles, global->params.dongle_number);
		}
		fill_coder(&(global->coders[i]), i, global);
		i++;
	}
	return (0);
}

// __builtin_printf("=== CODER #%d ===\n", coder->index);
// __builtin_printf("  Left hand:        %p\n", (void *)coder->first_dongle);
// __builtin_printf("  Right hand:       %p\n", (void *)coder->second_dongle);
// __builtin_printf("  Last compilation: %d\n", coder->last_compilation);
// __builtin_printf("  Compilation nb:   %d\n", coder->compilation_number);
// __builtin_printf("  Thread:           %p\n", (void *)coder->thread);
// __builtin_printf("  global:             %p\n", (void *)coder->global);
// __builtin_printf("\n");