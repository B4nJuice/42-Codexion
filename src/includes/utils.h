/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:14:22 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/12 10:03:11 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "coder.h"

void		codexion_log(t_coder coder, const char *description);
t_params	*fill_params(char **argv);
void		start_timestamp(void);
int			get_timestamp(void);

#endif