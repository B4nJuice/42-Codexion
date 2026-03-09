/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_coders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:12:22 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/09 13:26:31 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "coder.h"

void	fill_coder(t_coder *coder, int index, t_coder_first_check first_check)
{
	coder->index = index;
	coder->left_hand = 0;
	coder->right_hand = 0;
	coder->state = IDLE;
	coder->first_check = first_check;
}

t_coder	*create_coders(int number)
{
	t_coder				*array;
	t_coder_first_check	first_check;
	int					i;

	first_check = LEFT;
	array = malloc(number * sizeof(t_coder));
	if (!array)
		return (NULL);
	i = 0;
	while (i < number)
	{
		if (i == number - 1)
			first_check = RIGHT;
		fill_coder(&(array[i]), i, first_check);
		i++;
	}
	return (array);
}
