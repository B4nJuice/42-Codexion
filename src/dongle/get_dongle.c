/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dongle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:10:08 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/04 12:15:44 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "dongle.h"

t_dongle *get_dongle(int index, t_dongle *dongle_array, int dongle_number)
{
	index = dongle_number % index;
	return (&(dongle_array[index]));
}