/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 20:46:08 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/19 23:16:46 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	autocom(t_line *line)
{
	char	*command;
	char	*path;
	t_hash	*hash;
	size_t	i;
	size_t	len;

	command = line->buffer.buffer;
	i = 0;
	len = ft_strlen(command);
	path = NULL;
	while (i < g_bin_table.size)
	{
		hash = g_bin_table.table[i];
		while (hash)
		{
			if ((path = ft_strrchr((char*)hash->data, '/')))
			{
				if (!ft_strncmp(++path, command, len))
				{
					print_symb(path + len, line);
					return;
				}
			}
			hash = hash->next;
		}
		++i;
	}
}

void	find_bin(char *str, t_line)
{
	static char	**binary;


}
