/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 09:24:57 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/12 09:58:22 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "coder.h"

void	codexion_log(t_coder coder, const char *description)
{
	static int	stop = 0;
	int			time;

	if (!strcmp(description, "stop"))
		stop = 1;
	if (!stop)
	{
		time = get_timestamp();
		printf("%d %d %s\n", time, coder.index + 1, description);
	}
	if (!strcmp(description, "burned out"))
		stop = 1;
}
