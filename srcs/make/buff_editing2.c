/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_editing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 21:35:22 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/24 17:01:49 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char		*copy_from_buff(char *buffer, char *new_buffer, short start, short end)
{
	short	j;

	j = 0;
	while (start <= end)
		new_buffer[j++] = buffer[start++];
	return (new_buffer);
}

char		check_print_arr(char *arr)
{
	short	i;

	i = -1;
	while (arr[++i])
	{
		if (ft_isprint(arr[i]) && arr[i] != ' ')
			return (1);
	}
	return (0);
}

short	is_start_pos(t_cord *cord)
{
	if ((cord->x_cur == cord->x_start) && (cord->y_cur == cord->y_start))
		return (1);
	return (0);
}

void	unset_start_pos(t_cord	*cord)
{
	cord->x_start = 0;
	cord->y_start = 0;
}
