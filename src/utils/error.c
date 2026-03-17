/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:40:21 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/17 11:54:18 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	malloc_error(void *param1, void *param2, void *param3, void *param4)
{
	free(param1);
	free(param2);
	free(param3);
	free(param4);
	fprintf(stderr, "Malloc ERROR.\n");
	return (1);
}
