/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:14:22 by lgirard           #+#    #+#             */
/*   Updated: 2026/06/02 12:14:39 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "core.h"

int		fill_params(char **argv, int argc, t_params* params);
void	codexion_log(t_coder *coder, const char *description);
int		thread_destroy(t_global *global, int fail);
int		init_threads(t_global *global);
void	stop_running(t_global *global);
int 	is_running(t_global *global);
int		malloc_error(void *param);
void	start_timestamp(void);
int		get_timestamp(void);

#endif