/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:12:43 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/04 12:04:22 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

typedef enum e_coder_state
{
	IDLE,
	COMPILING,
	DEBUGGING,
	REFACTORING,
	BURNED_OUT
}	t_coder_state;

typedef struct s_coder
{
	int				index;
	int				left_hand;
	int				right_hand;
	t_coder_state	state;
}	t_coder;

t_coder	*create_coders(int number);

#endif