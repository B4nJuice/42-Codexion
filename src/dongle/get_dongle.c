/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dongle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:10:08 by lgirard           #+#    #+#             */
/*   Updated: 2026/05/28 10:24:58 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_dongle	*get_dongle(int index, t_dongle *dongle_array, int dongle_number)
{
	index = index % dongle_number;
	return (&(dongle_array[index]));
}
