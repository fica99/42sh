/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 21:00:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/27 21:50:15 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	free_cord(t_cord **cord)
{
	t_cord	*copy;
	t_cord	*nl;

	if (!*cord)
		return ;
	nl = *cord;
	while(nl)
	{
		copy = nl;
		nl = nl->nl;
		ft_memdel((void**)&copy);
	}
	*cord = NULL;
}

void	unset_start_pos(t_cord	*cord)
{
	cord->x_start = 0;
	cord->y_start = 0;
}
