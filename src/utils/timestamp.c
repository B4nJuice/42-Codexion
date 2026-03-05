/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:27:29 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/04 12:41:03 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>

void	start_timestamp(void);

int	get_timestamp(void)
{
	struct timeval		tv;
	struct timezone		tz;
	int					ms_time;

	ms_time = gettimeofday(&tv, &tz);
}
