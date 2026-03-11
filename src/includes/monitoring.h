/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirard <lgirard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 09:15:16 by lgirard           #+#    #+#             */
/*   Updated: 2026/03/11 10:18:55 by lgirard          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITORING_H
# define MONITORING_H
# include "coder.h"

typedef struct s_monitoring_args
{
	t_coder		**coders;
	t_params	params;
	int			*stop;
}	t_monitoring_args;

#endif