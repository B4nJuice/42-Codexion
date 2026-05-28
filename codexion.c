/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:30:00 by lgirard           #+#    #+#             */
/*   Updated: 2026/05/28 13:39:25 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "core.h"
#include "utils.h"
#include "monitoring.h"

int init_threads(t_global *global)
{
	int	i = 0;

	pthread_mutex_init(&(global->stop_mutex), NULL);
	pthread_mutex_init(&(global->print_mutex), NULL);

	start_timestamp();
	while(i < global->params.dongle_number)
	{
		pthread_create(&global->coders[i].thread, NULL, coder_routine, &global->coders[i]);
		if(!(global->coders[i].thread))
			return thread_destroy(global, i);
		pthread_mutex_init(&(global->coders[i].mutex), NULL);
		pthread_mutex_init(&(global->dongles[i].mutex), NULL);
		i++;
	}
	start_monitor(global);
	return (0);
}

int main(int ac, char **av)
{
	static t_global		global = {0};

	if (fill_params(av, ac, &(global.params)))
		return (1);
	if (create_dongles(&global))
		return (1);
	if (create_coders(&global))
		return (1);		
	if(init_threads(&global))
		return (1);
	// if (!threads)
	// 	return (malloc_error((void *)coders,
	// 	(void *)dongles, (void *)params, (void *)threads));
	// i = 0;
	// stop = 0;
	// while (i < params->dongle_number)
	// {
	// 	global = malloc(sizeof(t_global));
	// 	global->coder = &coders[i];
	// 	global->dongles = dongles;
	// 	global->params = *params;
	// 	global->stop = &stop;
	// 	pthread_create(&threads[i], NULL, coder_routine, global);
	// 	i++;
	// }
	// start_timestamp();
	// mglobal = malloc(sizeof(t_monitoring_global));
	// mglobal->coders = &coders;
	// mglobal->params = *params;
	// mglobal->stop = &stop;
	// pthread_create(&threads[i], NULL, monitoring_routine, mglobal);
	// i = 0;
	// while (i < params->dongle_number)
	// {
	// 	pthread_join(threads[i], NULL);
	// 	i++;
	// }
	thread_destroy(&global, global.params.dongle_number);
	free(global.coders);
	free(global.dongles);
	return (0);
}
