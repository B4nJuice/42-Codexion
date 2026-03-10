/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:32:00 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/10 10:44:19 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "coder.h"
#include "dongle.h"
#include "utils.h"

t_simulation	*g_sim = NULL;

typedef struct s_coder_args
{
	t_coder	*coder;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		dongle_cooldown;
}	t_coder_args;

static int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\f' || *str == '\v')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	main(int argc, char **argv)
{
	pthread_t		*threads;
	t_coder_args	*args;
	int				i;

	if (argc != 9)
	{
		fprintf(stderr, "Usage: %s number_of_coders time_to_burnout ", argv[0]);
		fprintf(stderr, "time_to_compile time_to_debug time_to_refactor ");
		fprintf(stderr, "number_of_compiles_required dongle_cooldown scheduler\n");
		return (1);
	}

	g_sim = malloc(sizeof(t_simulation));
	if (!g_sim)
		return (1);

	g_sim->num_coders = ft_atoi(argv[1]);
	g_sim->time_to_burnout = ft_atoi(argv[2]);
	g_sim->time_to_compile = ft_atoi(argv[3]);
	g_sim->time_to_debug = ft_atoi(argv[4]);
	g_sim->time_to_refactor = ft_atoi(argv[5]);
	g_sim->num_compiles_required = ft_atoi(argv[6]);
	g_sim->dongle_cooldown = ft_atoi(argv[7]);
	g_sim->scheduler = argv[8];
	
	if (g_sim->num_coders <= 0 || g_sim->time_to_burnout <= 0 ||
		g_sim->time_to_compile <= 0 || g_sim->time_to_debug <= 0 ||
		g_sim->time_to_refactor <= 0 || g_sim->num_compiles_required <= 0 ||
		g_sim->dongle_cooldown < 0)
	{
		fprintf(stderr, "Error: Invalid arguments\n");
		free(g_sim);
		return (1);
	}

	g_sim->simulation_end = 0;
	pthread_mutex_init(&g_sim->log_mutex, NULL);
	pthread_mutex_init(&g_sim->sim_mutex, NULL);
	pthread_cond_init(&g_sim->sim_end_cond, NULL);

	start_timestamp();

	g_sim->coders = create_coders(g_sim->num_coders);
	if (!g_sim->coders)
	{
		fprintf(stderr, "Error: Failed to create coders\n");
		free(g_sim);
		return (1);
	}

	g_sim->dongles = create_dongles(g_sim->num_coders);
	if (!g_sim->dongles)
	{
		fprintf(stderr, "Error: Failed to create dongles\n");
		free(g_sim->coders);
		free(g_sim);
		return (1);
	}

	g_sim->compile_count = malloc(sizeof(int) * g_sim->num_coders);
	if (!g_sim->compile_count)
	{
		fprintf(stderr, "Error: Failed to allocate compile count\n");
		destroy_dongles(g_sim->dongles, g_sim->num_coders);
		free(g_sim->coders);
		free(g_sim);
		return (1);
	}

	g_sim->last_compile_start = malloc(sizeof(int) * g_sim->num_coders);
	if (!g_sim->last_compile_start)
	{
		fprintf(stderr, "Error: Failed to allocate last compile start\n");
		free(g_sim->compile_count);
		destroy_dongles(g_sim->dongles, g_sim->num_coders);
		free(g_sim->coders);
		free(g_sim);
		return (1);
	}

	i = 0;
	while (i < g_sim->num_coders)
	{
		g_sim->compile_count[i] = 0;
		g_sim->last_compile_start[i] = 0;
		i++;
	}

	threads = malloc(sizeof(pthread_t) * g_sim->num_coders);
	if (!threads)
	{
		fprintf(stderr, "Error: Failed to allocate threads\n");
		free(g_sim->last_compile_start);
		free(g_sim->compile_count);
		destroy_dongles(g_sim->dongles, g_sim->num_coders);
		free(g_sim->coders);
		free(g_sim);
		return (1);
	}

	i = 0;
	while (i < g_sim->num_coders)
	{
		args = malloc(sizeof(t_coder_args));
		if (!args)
		{
			fprintf(stderr, "Error: Failed to allocate thread args\n");
			free(threads);
			free(g_sim->last_compile_start);
			free(g_sim->compile_count);
			destroy_dongles(g_sim->dongles, g_sim->num_coders);
			free(g_sim->coders);
			free(g_sim);
			return (1);
		}
		args->coder = &g_sim->coders[i];
		args->time_to_burnout = g_sim->time_to_burnout;
		args->time_to_compile = g_sim->time_to_compile;
		args->time_to_debug = g_sim->time_to_debug;
		args->time_to_refactor = g_sim->time_to_refactor;
		args->dongle_cooldown = g_sim->dongle_cooldown;
		pthread_create(&threads[i], NULL, coder_routine, args);
		i++;
	}

	i = 0;
	while (i < g_sim->num_coders)
	{
		pthread_join(threads[i], NULL);
		i++;
	}

	free(threads);
	free(g_sim->last_compile_start);
	free(g_sim->compile_count);
	destroy_dongles(g_sim->dongles, g_sim->num_coders);
	free(g_sim->coders);
	pthread_mutex_destroy(&g_sim->log_mutex);
	pthread_mutex_destroy(&g_sim->sim_mutex);
	pthread_cond_destroy(&g_sim->sim_end_cond);
	free(g_sim);
	return (0);
}
