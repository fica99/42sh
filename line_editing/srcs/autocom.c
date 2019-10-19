/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 20:46:08 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/19 20:55:22 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	autocom(t_line *line)
{
	char	*command;
	size_t		i;

	if (!(command = ft_strrchr(line->buffer.buffer, ' ')))
		command = line->buffer.buffer;
	else
		++command;
	i = 0;
	while (i < g_bin_table.size)
	{
		if (!ft_strnstr(g_bin_table.table[i]->data, command, ft_strlen(command)))
			break;
		++i;
	}
	ft_putstr_fd(g_bin_table.table[i]->data, STDIN_FILENO);
}
