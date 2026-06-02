/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:30:00 by lgirard           #+#    #+#             */
/*   Updated: 2026/06/02 12:14:04 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "core.h"
#include "utils.h"
#include "monitoring.h"

int	main(int ac, char **av)
{
	static t_global		global = {0};

	if (fill_params(av, ac, &(global.params)))
		return (1);
	if (create_dongles(&global))
		return (1);
	if (create_coders(&global))
		return (1);
	if (init_threads(&global))
		return (1);
	start_monitor(&global);
	thread_destroy(&global, global.params.dongle_number);
	free(global.coders);
	free(global.dongles);
	return (0);
}
