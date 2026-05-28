/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:17:45 by lgirard           #+#    #+#             */
/*   Updated: 2026/05/28 08:56:17 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_H
# define DONGLE_H

# include <pthread.h>

typedef struct s_dongle
{
	int				taken;
	int				last_time_taken;
	pthread_mutex_t	mutex;
}	t_dongle;

t_dongle	*create_dongles(int number);
void		destroy_dongles(t_dongle *dongles, int number);
t_dongle	*get_dongle(int index, t_dongle *dongle_array, int dongle_number);

#endif
