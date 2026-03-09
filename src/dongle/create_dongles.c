/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_dongles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:21:55 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/09 13:35:45 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include <pthread.h>
#include "dongle.h"

void	fill_dongle(t_dongle *dongle)
{
	dongle->taken = 0;
	dongle->last_time_taken = 0;
	pthread_mutex_init(&dongle->mutex, NULL);
}

t_dongle	*create_dongles(int number)
{
	t_dongle	*array;
	int			i;

	array = malloc(number * sizeof(t_dongle));
	if (!array)
		return (NULL);
	i = 0;
	while (i < number)
	{
		fill_dongle(&(array[i]));
		i++;
	}
	return (array);
}
