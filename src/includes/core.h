/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:12:43 by lgirard           #+#    #+#             */
/*   Updated: 2026/06/02 12:20:52 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include <pthread.h>

typedef struct s_coder	t_coder;

typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;

typedef enum e_coder_first_check
{
	LEFT,
	RIGHT
}	t_coder_first_check;

typedef struct s_dongle
{
	int				taken;
	int				last_time_taken;
	t_coder			*coder1;
	t_coder			*coder2;
	pthread_mutex_t	mutex;
}	t_dongle;

typedef struct s_params
{
	int			dongle_number;
	int			burnout_time;
	int			compiling_time;
	int			debugging_time;
	int			refactoring_time;
	int			required_compile;
	int			dongle_cooldown;
	const char	*scheduler_text;
	t_scheduler	scheduler;
}	t_params;

typedef struct s_global
{
	struct s_coder	*coders;
	t_dongle		*dongles;
	t_params		params;
	int				start_status;
	pthread_cond_t	cond;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	start_mutex;
	int				stop;
}	t_global;

typedef struct s_coder
{
	int					index;
	int					last_compilation;
	int					compilation_number;
	pthread_mutex_t		mutex;
	pthread_t			thread;
	t_dongle			*first_dongle;
	t_dongle			*second_dongle;
	t_global			*global;
}	t_coder;

/* Coder functions */
void		release_dongle(t_dongle *dongle, int mode);
int			create_coders(t_global *global);
int			take_dongles(t_coder *coder);
void		*coder_routine(void *arg);

/* Dongle functions */
t_dongle	*get_dongle(int index, t_dongle *dongle_array, int dongle_number);
void		ft_swap_dongle(t_dongle *dongle, t_scheduler scheduler);
int			create_dongles(t_global *global);

#endif
