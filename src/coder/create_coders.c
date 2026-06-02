/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_coders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:12:22 by lgirard           #+#    #+#             */
/*   Updated: 2026/06/02 12:24:59 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "stdio.h"
#include "core.h"
#include "utils.h"

void	fill_coder(t_coder *coder, int index, t_global *global)
{
	coder->index = index;
	coder->last_compilation = -1;
	coder->compilation_number = 0;
	coder->global = global;
}

int	create_coders(t_global *global)
{
	int					i;

	global->coders = malloc(global->params.dongle_number * sizeof(t_coder));
	if (!(global->coders))
		return (malloc_error(NULL));
	i = 0;
	while (i < global->params.dongle_number)
	{
		global->coders[i].first_dongle = get_dongle(i + \
(i == global->params.dongle_number - 1), \
global->dongles, global->params.dongle_number);
		global->coders[i].second_dongle = get_dongle(i + \
!(i == global->params.dongle_number - 1), global->dongles, \
global->params.dongle_number);
		fill_coder(&(global->coders[i]), i, global);
		i++;
	}
	return (0);
}
