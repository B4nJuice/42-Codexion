/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:30:00 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/12 10:19:28 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "coder.h"
#include "dongle.h"
#include "utils.h"


int main(int ac, char **av)
{
	t_params	*params;

	if (ac == 9)
	{
		params = fill_params(av);
		if (!params)
			return (1);
	}
	else
		fprintf(stderr, "Invalid arguments, try: ./codexion [number_of_coders]\
[time_to_burnout] [time_to_compile] [time_to_debug] [time_to_refactor]\
[number_of_compiles_required] [dongle_cooldown] [scheduler]\n");
	return (1);
}
