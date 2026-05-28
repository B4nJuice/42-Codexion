/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_coders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:12:22 by lgirard           #+#    #+#             */
/*   Updated: 2026/05/28 08:50:13 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "coder.h"

void	fill_coder(t_coder *coder, int index, t_coder_first_check first_check,\
	t_params params)
{
	coder->index = index;
	coder->left_hand = 0;
	coder->right_hand = 0;
	coder->state = IDLE;
	coder->first_check = first_check;
	coder->last_compilation = 0;
	coder->params = params;
}

t_coder	*create_coders(t_params params)
{
	t_coder				*array;
	t_coder_first_check	first_check;
	int					i;

	first_check = LEFT;
	array = malloc(params.dongle_number * sizeof(t_coder));
	if (!array)
		return (NULL);
	i = 0;
	while (i < params.dongle_number)
	{
		if (i == params.dongle_number - 1)
			first_check = RIGHT;
		fill_coder(&(array[i]), i, first_check, params);
		i++;
	}
	return (array);
}
