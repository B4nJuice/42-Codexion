/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:17:45 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/04 12:15:58 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_H
# define DONGLE_H

typedef struct s_dongle
{
	int		taken;
	int		last_time_taken;
}	t_dongle;

t_dongle	*create_dongles(int number);
t_dongle *get_dongle(int index, t_dongle *dongle_array, int dongle_number);

#endif
