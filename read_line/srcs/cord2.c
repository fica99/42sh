/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cord2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 20:08:49 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/23 20:25:37 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_shell.h"

void	set_start_params(void)
{
	get_win_size(g_line.cord);
	get_cur_cord(g_line.cord);
	set_start_cord(g_line.cord);
	set_end_cord(g_line.cord);
}
