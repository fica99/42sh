/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_bins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:19:27 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/23 16:55:43 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*ac_get_bin(char *command)
{
	static size_t	i;
	t_hash			*hash;
	int				len;
	char			*data;

	len = ft_strlen(command);
	while (i < g_bin_table.size)
	{
		hash = g_bin_table.table[i];
		while (hash)
		{
			if ((data = ft_strrchr((char*)hash->data, '/')))
			{
				if (!ft_strncmp(command, ++data, len))
				{
					++i;
					return (data);
				}
			}
			hash = hash->next;
		}
		++i;
	}
	i = 0;
	return (NULL);
}

void	ac_bins(char *command, t_line *line)
{
	char	*bin[g_bin_table.size];
	int		i;
	short	pos;

	if (!command)
		return ;
	i = 0;
	while ((bin[i] = ac_get_bin(command)))
		++i;
	if (i == 1)
		print_symb(bin[0] + ft_strlen(command), line);
	else if (i > 1)
	{
		pos = line->cord->pos;
		go_right(ft_strlen(line->buffer.buffer + pos), line->cord);
		ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
		ft_putchar_fd(NEW_LINE, STDIN_FILENO);
		ac_print_params(bin, line->cord->ws_col);
		g_line_flags |= AUTOCOM;
		line->cord->pos = pos;
		k_enter(line);
	}
}
