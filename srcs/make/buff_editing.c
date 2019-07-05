/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:25:22 by filip             #+#    #+#             */
/*   Updated: 2019/07/05 18:29:16 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char		*copy_from_buff(char *buffer, char *new_buffer, short start,
short end)
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

	if (!arr || !*arr)
		return (0);
	i = -1;
	while (arr[++i])
	{
		if (ft_isprint(arr[i]) && arr[i] != ' ')
			return (1);
	}
	return (0);
}
