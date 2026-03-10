/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 09:24:57 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/10 10:12:17 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "utils.h"
#include "coder.h"

void	codexion_log(t_coder coder, const char *description)
{
	int	time;

	time = get_timestamp();
	printf("%d %d %s\n", time, coder.index + 1, description);
}