/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_coders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:12:22 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/04 10:57:17 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "coder.h"

void	fill_coder(t_coder *coder, int index)
{
	coder->index = index;
	coder->left_hand = 0;
	coder->right_hand = 0;
	coder->state = IDLE;
}

t_coder	*create_coders(int number)
{
	t_coder		*array;
	int			i;

	array = malloc(number * sizeof(t_coder));
	if (!array)
		return (NULL);
	i = 0;
	while (i < number)
	{
		fill_coder(&(array[i]), i);
		i++;
	}
	return array;
}
