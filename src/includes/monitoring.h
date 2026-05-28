/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 09:15:16 by lgirard           #+#    #+#             */
/*   Updated: 2026/05/28 10:30:30 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITORING_H
# define MONITORING_H
# include "core.h"

typedef struct s_monitoring_global
{
	t_coder		**coders;
	t_params	params;
	int			*stop;
}	t_monitoring_global;

void	*monitoring_routine(void *arg);

#endif