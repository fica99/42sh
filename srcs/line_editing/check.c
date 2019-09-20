/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 17:30:00 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/20 17:30:32 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

short		is_start_pos(t_cord *cord)
{
	if ((cord->x_cur == cord->x_start) && (cord->y_cur == cord->y_start))
		return (1);
	return (0);
}
