/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 09:24:57 by lgirard           #+#    #+#             */
/*   Updated: 2026/05/28 13:48:58 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "core.h"

void	codexion_log(t_coder *coder, const char *description)
{
	pthread_mutex_lock(&(coder->global->print_mutex));
	if (is_running(coder->global))
		printf("%d %d %s\n", get_timestamp(), coder->index + 1, description);
	pthread_mutex_unlock(&(coder->global->print_mutex));
}
