/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:12:43 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/11 09:44:18 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include "dongle.h"

typedef enum e_coder_state
{
	IDLE,
	COMPILING,
	DEBUGGING,
	REFACTORING,
	BURNED_OUT
}	t_coder_state;

typedef enum e_coder_first_check
{
	LEFT,
	RIGHT
}	t_coder_first_check;

typedef struct s_coder
{
	int					index;
	int					left_hand;
	int					right_hand;
	int					last_compilation;
	int					compilation_number;
	t_coder_state		state;
	t_coder_first_check	first_check;
}	t_coder;

typedef struct s_params
{
	int			dongle_number;
	int			compiling_time;
	int			debugging_time;
	int			refactoring_time;
	int			burnout_time;
	int			required_compile;
}	t_params;

typedef struct s_thread_args
{
	t_coder		*coder;
	t_dongle	*dongles;
	t_params	params;
}	t_thread_args;

t_coder	*create_coders(int number);
void	*coder_routine(void *arg);
void	release_dongles(t_coder *coder, t_dongle *dongle_array,
			int dongle_number);
int		take_dongles(t_coder *coder, t_dongle *dongle_array, int dongle_number);

#endif