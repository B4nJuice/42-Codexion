/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:13:57 by lgirard           #+#    #+#             */
/*   Updated: 2026/06/02 12:15:34 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "utils.h"

static void	init_mutex(t_global *global)
{
	pthread_mutex_init(&(global->stop_mutex), NULL);
	pthread_mutex_init(&(global->print_mutex), NULL);
	pthread_mutex_init(&(global->start_mutex), NULL);
}

int	init_threads(t_global *global)
{
	int	i;

	i = 0;
	init_mutex(global);
	pthread_cond_init(&global->cond, NULL);
	while(i < global->params.dongle_number)
	{
		pthread_mutex_init(&(global->coders[i].mutex), NULL);
		pthread_mutex_init(&(global->dongles[i].mutex), NULL);
		pthread_create(&global->coders[i].thread, NULL, coder_routine,\
			&global->coders[i]);
		global->dongles[i].coder1 = &(global->coders[i * (i%2) + ((i + global->params.dongle_number - 1) % global->params.dongle_number) * !(i%2)]);
		global->dongles[i].coder2 = &(global->coders[i * !(i%2) + ((i + global->params.dongle_number - 1) % global->params.dongle_number) * (i%2)]);
		if (!(global->coders[i].thread))
			return (thread_destroy(global, i));
		i++;
	}
	return (0);
}