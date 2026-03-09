/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:27:29 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/09 18:12:02 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>

static struct timeval	*get_start_time(void)
{
	static struct timeval	start_time;

	return (&start_time);
}

void	start_timestamp(void)
{
	gettimeofday(get_start_time(), NULL);
}

int	get_timestamp(void)
{
	struct timeval			current_time;
	struct timeval			*start_time;
	long					seconds;
	long					microseconds;
	int						ms_time;

	start_time = get_start_time();
	gettimeofday(&current_time, NULL);
	seconds = current_time.tv_sec - start_time->tv_sec;
	microseconds = current_time.tv_usec - start_time->tv_usec;
	ms_time = (seconds * 1000) + (microseconds / 1000);
	return (ms_time);
}
